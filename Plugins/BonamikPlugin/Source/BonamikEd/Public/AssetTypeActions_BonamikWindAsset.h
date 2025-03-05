#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "AssetTypeActions_Base.h"
#include "SQEX_BonamikWind_Asset.h"

class FAssetTypeActions_BonamikWindAsset : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_BonamikWindAsset(EAssetTypeCategories::Type InAssetCategory)
            : AssetCategory(InAssetCategory)
        {}
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_BonamikWindAsset", "Bonamik Wind Asset"); }
	virtual FColor GetTypeColor() const override { return FColor::Magenta; }
	virtual UClass* GetSupportedClass() const override { return USQEX_BonamikWind_Asset::StaticClass(); }
	virtual uint32 GetCategories() override { return AssetCategory; }
    
private:
    EAssetTypeCategories::Type AssetCategory;
};
