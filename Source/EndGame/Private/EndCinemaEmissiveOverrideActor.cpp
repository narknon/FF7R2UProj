#include "EndCinemaEmissiveOverrideActor.h"
#include "EndCinemaEmissiveOverrideComponent.h"

AEndCinemaEmissiveOverrideActor::AEndCinemaEmissiveOverrideActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndCinemaEmissiveOverrideComponent>(TEXT("EmissiveOverrideComponent"));
    this->ControllerComponent = (UEndCinemaEmissiveOverrideComponent*)RootComponent;
    this->bLightVisibility = true;
    this->OverrideSeamlessInTime = -1.00f;
    this->OverrideSeamlessOutTime = -1.00f;
}


