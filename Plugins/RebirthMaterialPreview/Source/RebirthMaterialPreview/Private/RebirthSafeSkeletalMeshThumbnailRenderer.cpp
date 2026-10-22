#include "RebirthSafeSkeletalMeshThumbnailRenderer.h"

#include "Engine/SkeletalMesh.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "RebirthMaterialPreviewSafety.h"
#include "Rendering/SkeletalMeshRenderData.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthSkeletalThumbnailSafety, Log, All);

URebirthSafeSkeletalMeshThumbnailRenderer::URebirthSafeSkeletalMeshThumbnailRenderer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), DelegateRenderer(nullptr)
{
}

bool URebirthSafeSkeletalMeshThumbnailRenderer::SetDelegateRendererClass(UClass* RendererClass)
{
	if (!RendererClass || !RendererClass->IsChildOf(UThumbnailRenderer::StaticClass()) || RendererClass->IsChildOf(StaticClass()) || RendererClass->HasAnyClassFlags(CLASS_Abstract))
	{
		return false;
	}
	DelegateRendererClass = RendererClass;
	DelegateRenderer = nullptr;
	return true;
}

UThumbnailRenderer* URebirthSafeSkeletalMeshThumbnailRenderer::GetDelegateRenderer()
{
	if (!IsValid(DelegateRenderer) && DelegateRendererClass && !DelegateRendererClass->IsChildOf(StaticClass()))
	{
		DelegateRenderer = NewObject<UThumbnailRenderer>(this, DelegateRendererClass);
	}
	return DelegateRenderer;
}

bool URebirthSafeSkeletalMeshThumbnailRenderer::IsAllowed(UObject* Object, FString& OutReason) const
{
	if (!IsInGameThread())
	{
		OutReason = TEXT("skeletal_thumbnail_requires_game_thread");
		return false;
	}
	USkeletalMesh* Mesh = Cast<USkeletalMesh>(Object);
	if (!IsValid(Mesh) || Mesh->HasAnyFlags(RF_BeginDestroyed | RF_FinishDestroyed | RF_NeedLoad | RF_NeedPostLoad | RF_NeedPostLoadSubobjects))
	{
		OutReason = TEXT("skeletal_mesh_invalid_or_not_fully_loaded");
		return false;
	}
	const FSkeletalMeshRenderData* RenderData = Mesh->GetResourceForRendering();
	if (!RenderData || RenderData->LODRenderData.Num() == 0 || Mesh->RefSkeleton.GetNum() == 0 || Mesh->Materials.Num() == 0)
	{
		OutReason = TEXT("skeletal_mesh_missing_loaded_lods_skeleton_or_material_slots");
		return false;
	}
	// The native delegate creates/registers a skeletal component before drawing.
	// Check all original slots, including ones used only by a lower LOD, first.
	// Never load companions, compile shaders, set usage flags, or mutate a slot
	// from a Content Browser thumbnail callback.
	for (int32 Index = 0; Index < Mesh->Materials.Num(); ++Index)
	{
		UMaterialInterface* Material = Mesh->Materials[Index].MaterialInterface;
		const RebirthMaterialPreviewSafety::FResult Result = RebirthMaterialPreviewSafety::Evaluate(Material);
		if (!Result.bCanRender)
		{
			OutReason = FString::Printf(TEXT("material_slot_%d:%s:%s"), Index, *GetPathNameSafe(Material), *Result.Reason);
			return false;
		}
		UMaterial* BaseMaterial = Material->GetMaterial();
		if (!IsValid(BaseMaterial) || !BaseMaterial->GetUsageByFlag(MATUSAGE_SkeletalMesh))
		{
			OutReason = FString::Printf(TEXT("material_slot_%d:%s:missing_skeletal_mesh_usage"), Index, *GetPathNameSafe(Material));
			return false;
		}
	}
	OutReason.Reset();
	return true;
}

void URebirthSafeSkeletalMeshThumbnailRenderer::ReportBlocked(UObject* Object, const FString& Reason)
{
	const FString Asset = IsValid(Object) ? Object->GetPathName() : TEXT("<invalid>");
	if (!ReportedBlockedAssets.Contains(Asset))
	{
		ReportedBlockedAssets.Add(Asset);
		UE_LOG(LogRebirthSkeletalThumbnailSafety, Warning, TEXT("SkeletalMeshThumbnailBlocked asset=%s reason=%s"), *Asset, *Reason);
	}
}

bool URebirthSafeSkeletalMeshThumbnailRenderer::CanVisualizeAsset(UObject* Object)
{
	FString Reason;
	if (!IsAllowed(Object, Reason))
	{
		ReportBlocked(Object, Reason);
		return false;
	}
	UThumbnailRenderer* Delegate = GetDelegateRenderer();
	return Delegate && Delegate->CanVisualizeAsset(Object);
}

void URebirthSafeSkeletalMeshThumbnailRenderer::GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth, uint32& OutHeight) const
{
	FString Reason;
	UThumbnailRenderer* Delegate = IsAllowed(Object, Reason) ? const_cast<URebirthSafeSkeletalMeshThumbnailRenderer*>(this)->GetDelegateRenderer() : nullptr;
	if (Delegate)
	{
		Delegate->GetThumbnailSize(Object, Zoom, OutWidth, OutHeight);
	}
	else
	{
		Super::GetThumbnailSize(Object, Zoom, OutWidth, OutHeight);
	}
}

void URebirthSafeSkeletalMeshThumbnailRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* Viewport, FCanvas* Canvas, bool bAdditionalViewFamily)
{
	FString Reason;
	if (!IsAllowed(Object, Reason))
	{
		ReportBlocked(Object, Reason);
		return;
	}
	if (UThumbnailRenderer* Delegate = GetDelegateRenderer())
	{
		Delegate->Draw(Object, X, Y, Width, Height, Viewport, Canvas, bAdditionalViewFamily);
	}
}

bool URebirthSafeSkeletalMeshThumbnailRenderer::AllowsRealtimeThumbnails(UObject* Object) const
{
	FString Reason;
	UThumbnailRenderer* Delegate = IsAllowed(Object, Reason) ? const_cast<URebirthSafeSkeletalMeshThumbnailRenderer*>(this)->GetDelegateRenderer() : nullptr;
	return Delegate && Delegate->AllowsRealtimeThumbnails(Object);
}
