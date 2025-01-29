#include "RigUnit_EndLookAt_DebugSettings.h"

FRigUnit_EndLookAt_DebugSettings::FRigUnit_EndLookAt_DebugSettings() {
    this->bEnabled = false;
    this->Scale = 0.00f;
    this->BehaviorMode = EEndAnimBehaviorMode::Neutral;
    this->bForceComponentSpace = false;
    this->bEnableUpAxisLookAt = false;
}

