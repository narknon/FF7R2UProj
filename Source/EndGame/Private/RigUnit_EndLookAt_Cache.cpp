#include "RigUnit_EndLookAt_Cache.h"

FRigUnit_EndLookAt_Cache::FRigUnit_EndLookAt_Cache() {
    this->bNeedInitialize = false;
    this->ActiveTimer = 0.00f;
    this->ComponentSpaceOriginNormalRate = 0.00f;
    this->LocomotionState = EEndLocomotionState::Idle;
    this->IgnoreLookAtLayerCount = 0;
    this->KeepDirectionTimer = 0.00f;
    this->bForceComponentSpace = false;
    this->bEnableUpAxisLookAt = false;
    this->bEnabledTransitionCache0 = false;
    this->bEnabledTransitionCache1 = false;
    this->TransitionCurrentTime = 0.00f;
    this->TransitionTimeMax = 0.00f;
    this->TransitionCachedDeltaTime0 = 0.00f;
}

