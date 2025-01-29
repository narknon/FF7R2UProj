#include "RigUnit_EndFitGround_Cache.h"

FRigUnit_EndFitGround_Cache::FRigUnit_EndFitGround_Cache() {
    this->bNeedInitialize = false;
    this->bLastSetSeamlessOutSnapShotLocation = false;
    this->WalkRunAlpha = 0.00f;
    this->SlopeFitRate = 0.00f;
    this->WorldSpaceGroundHeightBlendRate = 0.00f;
    this->GroundDeltaHeight = 0.00f;
}

