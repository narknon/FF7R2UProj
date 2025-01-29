#include "EndVehicleTravelingSeSetting.h"

FEndVehicleTravelingSeSetting::FEndVehicleTravelingSeSetting() {
    this->OverrideAttenuation[0] = NULL;
    this->OverrideAttenuation[1] = NULL;
    this->OverrideAttenuation[2] = NULL;
    this->OverrideAttenuation[3] = NULL;
    this->NotGroundedVolumeMultiplier = 0.00f;
    this->AdjustSteeringInput_ZeroOneSlot0 = false;
    this->AdjustSteeringInput_ZeroOneValue = 0.00f;
}

