#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "AssetTypeActions_Base.h"
#include "EffectAppendixMesh.h"

class FAssetTypeActions_EffectAppendixMesh : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_EffectAppendixMesh(EAssetTypeCategories::Type InAssetCategory)
		: AssetCategory(InAssetCategory)
	{}

	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_EffectAppendixMesh", "Effect Appendix Mesh"); }
	virtual FColor GetTypeColor() const override { return FColor::Magenta; }
	virtual UClass* GetSupportedClass() const override { return UEffectAppendixMesh::StaticClass(); }  
	virtual uint32 GetCategories() override { return AssetCategory; }
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
    
private:
	EAssetTypeCategories::Type AssetCategory;
};