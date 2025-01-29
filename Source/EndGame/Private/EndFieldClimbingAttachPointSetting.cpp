#include "EndFieldClimbingAttachPointSetting.h"

UEndFieldClimbingAttachPointSetting::UEndFieldClimbingAttachPointSetting(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bStartOrFinishPoint = false;
    this->bStartIsTopEdge = false;
    this->bDisbleStart = false;
}


