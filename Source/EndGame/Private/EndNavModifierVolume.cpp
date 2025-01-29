#include "EndNavModifierVolume.h"
#include "NavAreas/NavArea_Default.h"

AEndNavModifierVolume::AEndNavModifierVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UNavArea_Default::StaticClass();
    this->Type = EModifierVolumeType::CoverPc;
    this->WallAffiliationID = 0;
    this->Wall = 0;
    this->Group = -1;
    this->WallBorder = false;
    this->SemiWallBorder = false;
    this->bCeil = false;
    this->bWallJumpAcceptFree = false;
    this->WallJumpExtentHeight = 400.00f;
    this->brushBuilderType = 0;
}


