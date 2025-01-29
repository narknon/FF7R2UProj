#include "EndWheeledVehicleAnimInstance.h"

UEndWheeledVehicleAnimInstance::UEndWheeledVehicleAnimInstance() {
    this->SuspensionMaxRaise = 0.00f;
    this->SuspensionMaxDrop = 0.00f;
    this->WheeledVehicleMovementComponent = NULL;
}

AEndWheeledVehicle* UEndWheeledVehicleAnimInstance::GetVehicle() const {
    return NULL;
}


