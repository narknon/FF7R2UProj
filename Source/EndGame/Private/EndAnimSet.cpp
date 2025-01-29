#include "EndAnimSet.h"

UEndAnimSet::UEndAnimSet() {
    this->bDisableLookAt = false;
    this->bComponentSpaceLookAt = false;
    this->BaseLookAtWeight = 1.00f;
    this->BodyLookAtWeight = 1.00f;
    this->HeadLookAtWeight = 1.00f;
    this->HandConstraintRate = 0.00f;
    this->bUseAim = false;
    this->bCanBeInCluster = false;
}


