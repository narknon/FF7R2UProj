#include "EndVehicleOneShotSeSetting.h"

FEndVehicleOneShotSeSetting::FEndVehicleOneShotSeSetting() {
    this->SwitchValueSourceType = EEndVehicleSwitchValueSourceTypes::None;
    this->OverrideAttenuation[0] = NULL;
    this->OverrideAttenuation[1] = NULL;
    this->OverrideAttenuation[2] = NULL;
    this->OverrideAttenuation[3] = NULL;
    this->OverrideConcurrency = NULL;
    this->MoveThreshold = 0.00f;
}

