#include "EndNavModifierInDoorVolume.h"
#include "EndNavAreaInDoor.h"

AEndNavModifierInDoorVolume::AEndNavModifierInDoorVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UEndNavAreaInDoor::StaticClass();
    this->CameraType = EEndFieldCameraInDoorType::Narrow;
    this->OverridePriorityType = EEndFieldCameraInDoorPriorityType::InDoor;
    this->SpecificMoveType = EEndSpecificMoveType::Walk;
    this->DashType = EEndDashType::Enable;
}


