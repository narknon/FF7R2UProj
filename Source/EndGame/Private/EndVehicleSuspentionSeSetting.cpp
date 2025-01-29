#include "EndVehicleSuspentionSeSetting.h"

FEndVehicleSuspentionSeSetting::FEndVehicleSuspentionSeSetting() {
    this->MoveVelocityThreshold = 0.00f;
    this->MoveOffsetHeightThreshold = 0.00f;
    this->ChassisHitVelocityThreshold = 0.00f;
    this->ChassisHitOffsetHeightThreshold = 0.00f;
    this->OverrideAttenuation[0] = NULL;
    this->OverrideAttenuation[1] = NULL;
    this->OverrideAttenuation[2] = NULL;
    this->OverrideAttenuation[3] = NULL;
    this->OverrideConcurrency = NULL;
    this->MoveSupressionTimeSec = 0.00f;
    this->HitSupressionTimeSec = 0.00f;
}

