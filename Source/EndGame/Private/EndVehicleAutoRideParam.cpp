#include "EndVehicleAutoRideParam.h"

FEndVehicleAutoRideParam::FEndVehicleAutoRideParam() {
    this->bEnableDirectRide = false;
    this->DirectRideWithInputDistance = 0.00f;
    this->DirectRideWithInputMaxYaw = 0.00f;
    this->DirectRideWithInputMinPower = 0.00f;
    this->ValidAngleRange = 0.00f;
    this->InvalideAutoRideTimer = 0.00f;
}

