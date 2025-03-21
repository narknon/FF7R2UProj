#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "AssetTypeActions_Base.h"
#include "EndDataObjectBase.h"

class FAssetTypeActions_EndDataObject : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_EndDataObject(EAssetTypeCategories::Type InAssetCategory)
            : AssetCategory(InAssetCategory)
        {}
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_EndDataObject", "End Data Object"); }
	virtual FColor GetTypeColor() const override { return FColor::Magenta; }
	virtual UClass* GetSupportedClass() const override { return UEndDataObjectBase::StaticClass(); }
	virtual uint32 GetCategories() override { return AssetCategory; }
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
    
private:
    EAssetTypeCategories::Type AssetCategory;
};
