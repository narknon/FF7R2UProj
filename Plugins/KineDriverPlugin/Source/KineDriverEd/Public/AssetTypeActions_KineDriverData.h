#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "AssetTypeActions_Base.h"
#include "SQEX_KineDriverData.h"

class FAssetTypeActions_KineDriverData : public FAssetTypeActions_Base
{
public:
    FAssetTypeActions_KineDriverData(EAssetTypeCategories::Type InAssetCategory)
            : AssetCategory(InAssetCategory)
        {}
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_KineDriverData", "KineDriver Data"); }
	virtual FColor GetTypeColor() const override { return FColor::Blue; }
	virtual UClass* GetSupportedClass() const override { return USQEX_KineDriverData::StaticClass(); }	
	virtual uint32 GetCategories() override { return AssetCategory; }
    
private:
    EAssetTypeCategories::Type AssetCategory;
};
