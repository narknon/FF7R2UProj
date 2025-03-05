#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "AssetTypeActions_Base.h"
#include "EndCameraSequence.h"

class FAssetTypeActions_EndCameraSequence : public FAssetTypeActions_Base
{
public:
    FAssetTypeActions_EndCameraSequence(EAssetTypeCategories::Type InAssetCategory)
            : AssetCategory(InAssetCategory)
        {}
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_EndCameraSequence", "End Camera Sequence"); }
	virtual FColor GetTypeColor() const override { return FColor::Magenta; }
	virtual UClass* GetSupportedClass() const override { return UEndCameraSequence::StaticClass(); }
	virtual uint32 GetCategories() override { return AssetCategory; }
    
private:
    EAssetTypeCategories::Type AssetCategory;
};
