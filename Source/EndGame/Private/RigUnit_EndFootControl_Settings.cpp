#include "RigUnit_EndFootControl_Settings.h"

FRigUnit_EndFootControl_Settings::FRigUnit_EndFootControl_Settings() {
    this->LandingHeightThreshold = 0.00f;
    this->FootTraceStartHeight = 0.00f;
    this->FootTraceEndHeight = 0.00f;
    this->FootTraceToeRate = 0.00f;
    this->HipOffsetApplyRateIdle = 0.00f;
    this->HipOffsetApplyRateWalk = 0.00f;
    this->HipOffsetApplyRateRun = 0.00f;
    this->bUseInterpSettingsWalk = false;
    this->bUseInterpSettingsRun = false;
    this->OverrideGroundTraceOffsetX = 0.00f;
    this->OverrideGroundTraceOffsetY = 0.00f;
    this->GroundNormalFitAngleMax = 0.00f;
    this->FootLengthBias = 0.00f;
    this->bApplyStairs = false;
    this->bUseFootLock = false;
    this->bDefaultFootLockActivation = false;
    this->FootLockTranslationRate = 0.00f;
    this->FootLockRotationRate = 0.00f;
    this->FootLockRateActiveInterpSpeed = 0.00f;
    this->FootLockRateDeactiveInterpSpeed = 0.00f;
    this->FootLockDeactivateWithExtraActionWaitTime = 0.00f;
    this->bMigrate = false;
}

