#include "EndFieldClimbingPointSettingBase.h"

UEndFieldClimbingPointSettingBase::UEndFieldClimbingPointSettingBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bDisableAutoSnapWall = false;
    this->bCachedCatchIndex = false;
    this->bCatchToHandSlide = false;
}


