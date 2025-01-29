#include "RigUnit_EndLookAt_Effector.h"

FRigUnit_EndLookAt_Effector::FRigUnit_EndLookAt_Effector() {
    this->bActive = false;
    this->TargetType = EEndLookAtRequestType::Cinema;
    this->Weight = 0.00f;
    this->bActiveSaccade = false;
    this->bOnlySaccade = false;
    this->DiffAngle = 0.00f;
    this->bUseAimBaseNormal = false;
    this->bSwitchDirectionKeeping = false;
    this->LookAwayDirectionType = 0;
    this->OverrideDeactiveBlendTime = 0.00f;
}

