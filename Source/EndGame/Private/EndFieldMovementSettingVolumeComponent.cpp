#include "EndFieldMovementSettingVolumeComponent.h"

UEndFieldMovementSettingVolumeComponent::UEndFieldMovementSettingVolumeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanEverAffectNavigation = false;
    this->MovementSettingFlag = 0;
    this->WaterMoveDepth = -1.00f;
    this->SwimmingWalkableAngle = -1.00f;
    this->CameraCustomSuspensionType = EEndCameraCustomSuspensionType::EEndCameraCustomSuspension_Default;
    this->OverridePhysicalMaterial = NULL;
}


