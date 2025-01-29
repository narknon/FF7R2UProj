#include "EndCinemaDirectionalLightOverrideActor.h"

AEndCinemaDirectionalLightOverrideActor::AEndCinemaDirectionalLightOverrideActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCascadeDistanceEnabled = true;
    this->CascadeDistance0 = 0.00f;
    this->CascadeDistance1 = 0.00f;
    this->bVisibilityEnabled = false;
    this->bVisibility = false;
}


