#include "RebirthCookedMaterialMetadata.h"

#include "Logging/LogMacros.h"
#include "MaterialCachedData.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UObjectIterator.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthCookedMaterialMetadata, Log, All);

namespace
{
	FDelegateHandle CookedMetadataAssetLoadedHandle;

	bool IsCookedMaterialPackage(const UMaterial* Material)
	{
		const UPackage* Package = Material ? Material->GetOutermost() : nullptr;
		return Package && (Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly));
	}

	template <typename T>
	bool PadMetadataArray(TArray<T>& Values, int32 Count, const T& Default)
	{
		if (Values.Num() >= Count)
		{
			return false;
		}
		Values.Reserve(Count);
		while (Values.Num() < Count)
		{
			Values.Add(Default);
		}
		return true;
	}

	/** ExpressionGuids and Overrides are read in parallel with ParameterInfos; a malformed entry is left alone. */
	bool PadMetadataEntry(FMaterialCachedParameterEntry& Entry)
	{
		const int32 Count = Entry.ParameterInfos.Num();
		if (Entry.NameHashes.Num() != Count)
		{
			return false;
		}
		bool bChanged = PadMetadataArray<FGuid>(Entry.ExpressionGuids, Count, FGuid());
		bChanged |= PadMetadataArray<bool>(Entry.Overrides, Count, false);
		return bChanged;
	}

	void OnCookedMetadataAssetLoaded(UObject* Object)
	{
		if (const UMaterialInterface* Material = Cast<UMaterialInterface>(Object))
		{
			RebirthCookedMaterialMetadata::RepairChain(Material);
		}
	}
}

namespace RebirthCookedMaterialMetadata
{
	bool Repair(UMaterial* Material)
	{
		if (!IsCookedMaterialPackage(Material))
		{
			return false;
		}
		// The engine only reads this cache; it is never rebuilt for cooked materials (UMaterial::UpdateCachedExpressionData
		// returns early for bIsCookedForEditor packages), so the padding stays until the material is unloaded.
		FMaterialCachedParameters& Parameters = const_cast<FMaterialCachedExpressionData&>(Material->GetCachedExpressionData()).Parameters;

		bool bChanged = false;
		for (FMaterialCachedParameterEntry& Entry : Parameters.RuntimeEntries)
		{
			bChanged |= PadMetadataEntry(Entry);
		}
		for (FMaterialCachedParameterEntry& Entry : Parameters.EditorOnlyEntries)
		{
			bChanged |= PadMetadataEntry(Entry);
		}

		const int32 Scalars = Parameters.GetNumParameters(EMaterialParameterType::Scalar);
		const int32 Vectors = Parameters.GetNumParameters(EMaterialParameterType::Vector);
		const int32 Textures = Parameters.GetNumParameters(EMaterialParameterType::Texture);
		const int32 Buffers = Parameters.GetNumParameters(EMaterialParameterType::ShaderResourceBuffer);
		const int32 Fonts = Parameters.GetNumParameters(EMaterialParameterType::Font);
		const int32 VirtualTextures = Parameters.GetNumParameters(EMaterialParameterType::RuntimeVirtualTexture);
		const int32 Switches = Parameters.GetNumParameters(EMaterialParameterType::StaticSwitch);
		const int32 Masks = Parameters.GetNumParameters(EMaterialParameterType::StaticComponentMask);

		// Runtime values are normally complete in cooked data; pad only if a value list is shorter than its parameter list.
		bChanged |= PadMetadataArray<float>(Parameters.ScalarValues, Scalars, 0.0f);
		bChanged |= PadMetadataArray<FLinearColor>(Parameters.VectorValues, Vectors, FLinearColor::Black);
		bChanged |= PadMetadataArray<UTexture*>(Parameters.TextureValues, Textures, nullptr);
		bChanged |= PadMetadataArray<UShaderResourceBuffer*>(Parameters.ShaderResourceBufferValues, Buffers, nullptr);
		bChanged |= PadMetadataArray<UFont*>(Parameters.FontValues, Fonts, nullptr);
		bChanged |= PadMetadataArray<int32>(Parameters.FontPageValues, Fonts, 0);
		bChanged |= PadMetadataArray<URuntimeVirtualTexture*>(Parameters.RuntimeVirtualTextureValues, VirtualTextures, nullptr);

		// Editor-only values stripped by the cook.
		FStaticComponentMaskValue NoMask;
		NoMask.R = NoMask.G = NoMask.B = NoMask.A = false;
		bChanged |= PadMetadataArray<bool>(Parameters.StaticSwitchValues, Switches, false);
		bChanged |= PadMetadataArray<FStaticComponentMaskValue>(Parameters.StaticComponentMaskValues, Masks, NoMask);
		bChanged |= PadMetadataArray<FVector2D>(Parameters.ScalarMinMaxValues, Scalars, FVector2D::ZeroVector);
		bChanged |= PadMetadataArray<UCurveLinearColor*>(Parameters.ScalarCurveValues, Scalars, nullptr);
		bChanged |= PadMetadataArray<UCurveLinearColorAtlas*>(Parameters.ScalarCurveAtlasValues, Scalars, nullptr);
		bChanged |= PadMetadataArray<FParameterChannelNames>(Parameters.VectorChannelNameValues, Vectors, FParameterChannelNames());
		bChanged |= PadMetadataArray<bool>(Parameters.VectorUsedAsChannelMaskValues, Vectors, false);
		bChanged |= PadMetadataArray<FParameterChannelNames>(Parameters.TextureChannelNameValues, Textures, FParameterChannelNames());

		if (bChanged)
		{
			UE_LOG(LogRebirthCookedMaterialMetadata, Log, TEXT("Filled stripped editor parameter metadata of cooked material %s (%d scalar, %d vector, %d texture parameters)."),
				*Material->GetPathName(), Scalars, Vectors, Textures);
		}
		return bChanged;
	}

	void RepairChain(const UMaterialInterface* Material)
	{
		TSet<const UMaterialInterface*> Seen;
		const UMaterialInterface* Current = Material;
		while (Current && !Seen.Contains(Current))
		{
			Seen.Add(Current);
			if (const UMaterial* Base = Cast<UMaterial>(Current))
			{
				Repair(const_cast<UMaterial*>(Base));
				return;
			}
			const UMaterialInstance* Instance = Cast<UMaterialInstance>(Current);
			Current = Instance ? Instance->Parent : nullptr;
		}
	}

	void Startup()
	{
		if (CookedMetadataAssetLoadedHandle.IsValid())
		{
			return;
		}
		int32 Repaired = 0;
		for (TObjectIterator<UMaterial> It; It; ++It)
		{
			Repaired += Repair(*It) ? 1 : 0;
		}
		CookedMetadataAssetLoadedHandle = FCoreUObjectDelegates::OnAssetLoaded.AddStatic(&OnCookedMetadataAssetLoaded);
		UE_LOG(LogRebirthCookedMaterialMetadata, Display, TEXT("Cooked material parameter metadata guard active (%d already loaded material(s) filled)."), Repaired);
	}

	void Shutdown()
	{
		if (CookedMetadataAssetLoadedHandle.IsValid())
		{
			FCoreUObjectDelegates::OnAssetLoaded.Remove(CookedMetadataAssetLoadedHandle);
			CookedMetadataAssetLoadedHandle.Reset();
		}
	}
}
