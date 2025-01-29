#include "RigUnit_EndFootControl_Cache.h"

FRigUnit_EndFootControl_Cache::FRigUnit_EndFootControl_Cache() {
    this->bNeedInitialize = false;
    this->bLastSetSeamlessOutSnapShotLocation = false;
    this->WalkRunAlpha = 0.00f;
    this->SlopeFitRate = 0.00f;
    this->WorldSpaceGroundHeightBlendRate = 0.00f;
    this->GroundDeltaHeight = 0.00f;
    this->NoHitTransformRatePitch = 0.00f;
    this->NoHitTransformRateRoll = 0.00f;
    this->FootLockDeactivateWithExtraActionWaitTimer = 0.00f;
}

