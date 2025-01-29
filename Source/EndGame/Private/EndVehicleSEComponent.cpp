#include "EndVehicleSEComponent.h"

UEndVehicleSEComponent::UEndVehicleSEComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bStartOnPlay = true;
    this->VelocityDetectionType = EEndVehicleSEVelocityDetectionTypes::EndCharaMovedVelocity;
    this->MeshComponent = NULL;
}


