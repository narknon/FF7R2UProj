#include "EndVehicleZeroOneModifierSetting.h"

FEndVehicleZeroOneModifierSetting::FEndVehicleZeroOneModifierSetting() {
    this->ZeroOneValueSourceType = EEndVehicleZeroOneValueSourceTypes::ScaledVelocity;
    this->MinZeroOneValue = 0.00f;
    this->MaxZeroOneValue = 0.00f;
    this->bEnableInputAccelAndDecelModify = false;
    this->AccelEasingFunc = EEasingFunc::Linear;
    this->DecelEasingFunc = EEasingFunc::Linear;
    this->InputAccelAndDecelModifyDuration = 0.00f;
    this->bUseThrottleInputAsModifyRate = false;
    this->bEnableInputJumpModify = false;
    this->JumpEasingFunc = EEasingFunc::Linear;
    this->ModifyJumpDuration = 0.00f;
}

