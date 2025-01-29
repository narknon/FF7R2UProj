#include "EndFieldActionChocoboUpdraftParam.h"

FEndFieldActionChocoboUpdraftParam::FEndFieldActionChocoboUpdraftParam() {
    this->MaxUpstreamSpeed = 0.00f;
    this->UpstreamAcceleration = 0.00f;
    this->UpstreamGravityScale = 0.00f;
    this->MaxHorizontalSpeed = 0.00f;
    this->MinHorizontalSpeed = 0.00f;
    this->HorizontalAcceleration = 0.00f;
    this->HorizontalDeceleration = 0.00f;
    this->bForceGlideMode = false;
    this->bForceBrake = false;
    this->Priority = 0;
    this->bApplyCeilLimit = false;
    this->AbsoluteUpperHeight = 0.00f;
    this->MinTimeForEnableApplyWithoutVolume = 0.00f;
    this->UpdraftTimeOut = 0.00f;
}

