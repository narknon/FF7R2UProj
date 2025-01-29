#include "EndFieldActionMovingMoogleFloorActor.h"

AEndFieldActionMovingMoogleFloorActor::AEndFieldActionMovingMoogleFloorActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->SpeedScale = 1.00f;
}


