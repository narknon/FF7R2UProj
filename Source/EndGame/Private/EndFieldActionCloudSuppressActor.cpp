#include "EndFieldActionCloudSuppressActor.h"

AEndFieldActionCloudSuppressActor::AEndFieldActionCloudSuppressActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->InputDownSpeedRate = 1.00f;
    this->NoInputReverseSpeedRate = 1.00f;
    this->DisableInputReverseSpeedRate = 1.00f;
}


