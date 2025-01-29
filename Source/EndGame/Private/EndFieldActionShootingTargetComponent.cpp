#include "EndFieldActionShootingTargetComponent.h"

UEndFieldActionShootingTargetComponent::UEndFieldActionShootingTargetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->TargetEnableRadius = 1000.00f;
    this->YuffiTargetEnableRadius = 3000.00f;
    this->TargetEnableCamDegrees = 90.00f;
    this->TargetEnableCharaDegrees = 180.00f;
    this->bDisableTargetIcon = false;
    this->bEnableRaycastCheckCharaToIcon = true;
    this->bIgnoreBarret = false;
    this->bIgnoreYuffi = false;
}


