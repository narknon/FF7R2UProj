#include "EndCinemaCameraManagerSettingActor.h"

AEndCinemaCameraManagerSettingActor::AEndCinemaCameraManagerSettingActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->LightClippingDistance = 0.00f;
}

void AEndCinemaCameraManagerSettingActor::SetLightClippingDistance(float InValue) {
}


