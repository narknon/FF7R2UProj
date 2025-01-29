#include "RigUnit_EndFitGround_Settings.h"

FRigUnit_EndFitGround_Settings::FRigUnit_EndFitGround_Settings() {
    this->bUseInterpSettingsWalk = false;
    this->bUseInterpSettingsRun = false;
    this->OverrideGroundTraceOffsetX = 0.00f;
    this->OverrideGroundTraceOffsetY = 0.00f;
    this->GroundNormalFitAngleMax = 0.00f;
    this->bMigrate = false;
}

