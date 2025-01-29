#include "GravityAndAirResistanceControl.h"

FGravityAndAirResistanceControl::FGravityAndAirResistanceControl() {
    this->EnableGravityControl = false;
    this->GravityControlStartTime = 0.00f;
    this->GravityControlRampUpTime = 0.00f;
    this->GravityControlEndTime = 0.00f;
    this->ExtraGravityMultiplier = 0.00f;
    this->EnableAirResistanceControl = false;
    this->AirResistanceOnlyPlanar = false;
    this->AirResistanceControlStartTime = 0.00f;
    this->AirResistanceControlRampUpTime = 0.00f;
    this->AirResistanceControlEndTime = 0.00f;
    this->AirResistanceMaxSpeed = 0.00f;
    this->AirResistanceStrength = 0.00f;
    this->AngularDamping = 0.00f;
    this->CleanupTime = 0.00f;
    this->DisableCollision = false;
    this->DisableCollisionStartTime = 0.00f;
    this->DisableCollisionStopTime = 0.00f;
}

