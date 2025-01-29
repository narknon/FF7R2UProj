#include "EndAIActionPackBase.h"

UEndAIActionPackBase::UEndAIActionPackBase() {
    this->bUseDistance = false;
    this->DistanceMin = 0.00f;
    this->DistanceMax = 0.00f;
    this->bUseHeight = false;
    this->HeightMin = 0.00f;
    this->HeightMax = 0.00f;
    this->bUseAngleYaw = false;
    this->AngleYaw = 0.00f;
    this->AngleYawOffset = 0.00f;
    this->bUseAnglePitch = false;
    this->AnglePitch = 0.00f;
    this->AnglePitchOffset = 0.00f;
    this->bDebugDisableLog = false;
}


