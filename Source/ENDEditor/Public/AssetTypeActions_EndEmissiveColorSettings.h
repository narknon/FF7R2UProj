#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "AssetTypeActions_Base.h"
#include "EndEmissiveColorSettings.h"

class FAssetTypeActions_EndEmissiveColorSettings : public FAssetTypeActions_Base
{
public:
    FAssetTypeActions_EndEmissiveColorSettings(EAssetTypeCategories::Type InAssetCategory)
            : AssetCategory(InAssetCategory)
        {}
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_EndEmissiveColorSettings", "End Emissive Color Settings"); }
	virtual FColor GetTypeColor() const override { return FColor::Magenta; }
	virtual UClass* GetSupportedClass() const override { return UEndEmissiveColorSettings::StaticClass(); }	
	virtual uint32 GetCategories() override { return AssetCategory; }
    
private:
    EAssetTypeCategories::Type AssetCategory;
};
