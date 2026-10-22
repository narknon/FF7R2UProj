#include "RebirthMaterialPreviewSafety.h"

#include "MaterialShared.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Misc/App.h"
#include "RHI.h"
#include "UObject/Package.h"

namespace RebirthMaterialPreviewSafety
{
	FResult Evaluate(UMaterialInterface* Material)
	{
		FResult Result;
		auto Fail = [&Result](const FString& Reason)
		{
			if (Result.Reason.IsEmpty())
			{
				Result.Reason = Reason;
			}
		};
		if (!IsInGameThread())
		{
			Result.Reason = TEXT("material_preview_requires_game_thread");
			return Result;
		}

		// Validate the explicit chain before calling recursive interface getters.
		TArray<UMaterialInterface*> Chain;
		TSet<UMaterialInterface*> Seen;
		UMaterialInterface* Current = Material;
		UMaterial* BaseMaterial = nullptr;
		while (Current)
		{
			if (!IsValid(Current) || Current->HasAnyFlags(RF_BeginDestroyed | RF_FinishDestroyed))
			{
				Result.Reason = TEXT("parent_chain_contains_invalid_or_destroying_object");
				return Result;
			}
			if (Seen.Contains(Current) || Chain.Num() >= 64)
			{
				Result.Reason = TEXT("parent_chain_cycle_or_depth_limit");
				return Result;
			}
			Seen.Add(Current);
			Chain.Add(Current);
			const UPackage* Package = Current->GetOutermost();
			Result.bUsesCookedChain |= Package && (Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly));
			if (Current->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad | RF_NeedPostLoadSubobjects))
			{
				Result.Reason = FString::Printf(TEXT("parent_not_fully_loaded:%s"), *Current->GetPathName());
				return Result;
			}
			if (UMaterialInstance* Instance = Cast<UMaterialInstance>(Current))
			{
				Current = Instance->Parent;
			}
			else
			{
				BaseMaterial = Cast<UMaterial>(Current);
				break;
			}
		}
		if (!BaseMaterial)
		{
			Result.Reason = TEXT("material_chain_has_no_supported_base_material");
			return Result;
		}
		Result.bParentChainValid = true;

		const int32 Domain = static_cast<int32>(BaseMaterial->MaterialDomain.GetValue());
		if (Domain < 0 || Domain >= MD_MAX)
		{
			Result.bHasUnsupportedRenderState = true;
			Fail(FString::Printf(TEXT("unsupported_material_domain:%s:%d"), *BaseMaterial->GetPathName(), Domain));
		}
		for (UMaterialInterface* Node : Chain)
		{
			const int32 Blend = static_cast<int32>(Node->GetBlendMode());
			if (Blend < 0 || Blend >= BLEND_MAX)
			{
				Result.bHasInvalidBlendMode = true;
				Result.bHasUnsupportedRenderState = true;
				Fail(FString::Printf(TEXT("unsupported_blend_mode:%s:%d"), *Node->GetPathName(), Blend));
			}
			if (!Node->GetShadingModels().IsValid())
			{
				Result.bHasUnsupportedRenderState = true;
				Fail(FString::Printf(TEXT("unsupported_shading_models:%s"), *Node->GetPathName()));
			}
		}
		if (!FApp::CanEverRender() || GMaxRHIShaderPlatform == SP_NumPlatforms)
		{
			Fail(TEXT("renderer_not_available"));
		}

		// Avoid resource getters if an invalid object-level render state already forbids rendering.
		if (!Result.Reason.IsEmpty())
		{
			return Result;
		}
		for (UMaterialInterface* Node : Chain)
		{
			const FMaterialResource* Resource = Node->GetMaterialResource(GMaxRHIFeatureLevel);
			if (!Resource)
			{
				Fail(FString::Printf(TEXT("missing_material_resource:%s"), *Node->GetPathName()));
				continue;
			}
			const int32 Blend = static_cast<int32>(Resource->GetBlendMode());
			if (Blend < 0 || Blend >= BLEND_MAX)
			{
				Result.bHasInvalidBlendMode = true;
				Result.bHasUnsupportedRenderState = true;
				Fail(FString::Printf(TEXT("unsupported_resource_blend_mode:%s:%d"), *Node->GetPathName(), Blend));
				continue;
			}
			const FMaterialShaderMap* Map = Resource->GetGameThreadShaderMap();
			if (!Map || !Map->GetContent() || !Map->GetResource())
			{
				Fail(FString::Printf(TEXT("missing_or_incomplete_shader_map:%s"), *Node->GetPathName()));
				continue;
			}
			if (!Map->IsCompilationFinalized() || !Map->CompiledSuccessfully() || Map->GetShaderNum() == 0 || Map->GetResource()->GetNumShaders() == 0)
			{
				Fail(FString::Printf(TEXT("shader_map_not_ready:%s"), *Node->GetPathName()));
			}
			else if (Map->GetShaderPlatform() != GMaxRHIShaderPlatform || Map->GetResource()->GetPlatform() != GMaxRHIShaderPlatform)
			{
				Fail(FString::Printf(TEXT("shader_platform_mismatch:%s:map=%d:resource=%d:active=%d"), *Node->GetPathName(), static_cast<int32>(Map->GetShaderPlatform()), static_cast<int32>(Map->GetResource()->GetPlatform()), static_cast<int32>(GMaxRHIShaderPlatform)));
			}
			else if (!Map->GetResource()->IsInitialized())
			{
				Fail(FString::Printf(TEXT("shader_resource_initialization_pending:%s"), *Node->GetPathName()));
			}
		}
		Result.bCanRender = Result.Reason.IsEmpty();
		return Result;
	}

	bool CanRender(UMaterialInterface* Material, bool& OutUsesCookedChain, FString& OutReason)
	{
		const FResult Result = Evaluate(Material);
		OutUsesCookedChain = Result.bUsesCookedChain;
		OutReason = Result.Reason;
		return Result.bCanRender;
	}

	bool CanRenderNativeThumbnail(UMaterialInterface* Material, FString& OutReason)
	{
		const FResult Result = Evaluate(Material);
		const bool bAllowed = Result.bParentChainValid && !Result.bHasUnsupportedRenderState && (!Result.bUsesCookedChain || Result.bCanRender);
		OutReason = bAllowed ? FString() : Result.Reason;
		return bAllowed;
	}
}
