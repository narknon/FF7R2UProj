#include "EndShootingCoasterSpeedTriggerBox.h"

AEndShootingCoasterSpeedTriggerBox::AEndShootingCoasterSpeedTriggerBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RailActorReference = NULL;
    this->MaxLength = 0.00f;
    this->AtLength = 0.00f;
    this->RideSpeed = 10.00f;
    this->LinearInterpolationTime = 0.10f;
}


