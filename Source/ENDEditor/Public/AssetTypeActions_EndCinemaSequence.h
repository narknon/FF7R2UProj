#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "AssetTypeActions_Base.h"
#include "EndCinemaSequence.h"

class FAssetTypeActions_EndCinemaSequence : public FAssetTypeActions_Base
{
public:
    FAssetTypeActions_EndCinemaSequence(EAssetTypeCategories::Type InAssetCategory)
            : AssetCategory(InAssetCategory)
        {}
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_EndCinemaSequence", "End Cinema Sequence"); }
	virtual FColor GetTypeColor() const override { return FColor::Magenta; }
	virtual UClass* GetSupportedClass() const override { return UEndCinemaSequence::StaticClass(); }
	virtual uint32 GetCategories() override { return AssetCategory; }
    
private:
    EAssetTypeCategories::Type AssetCategory;
};
