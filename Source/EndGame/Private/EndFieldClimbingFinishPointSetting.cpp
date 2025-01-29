#include "EndFieldClimbingFinishPointSetting.h"

UEndFieldClimbingFinishPointSetting::UEndFieldClimbingFinishPointSetting(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bFinishIsForceStepOn = false;
    this->bLongFallPoint = false;
    this->bShowEnterEffect = true;
    this->bAutoSnapEnterEffect = true;
    this->bUseManualEdge = false;
    this->bEdgeSearchFromForceBeforePointDir = false;
    this->bCachedEdgeTrans = false;
    this->bCachedFallFlag = false;
    this->bFallPointFlag = false;
}


