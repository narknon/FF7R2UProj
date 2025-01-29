#include "RigUnit_EndFootControl_FootCache.h"

FRigUnit_EndFootControl_FootCache::FRigUnit_EndFootControl_FootCache() {
    this->InitialFootHeight = 0.00f;
    this->InitialToeHeight = 0.00f;
    this->TotalFootLength = 0.00f;
    this->bValidWorldTransformCache = false;
    this->bLanding = false;
    this->bEnabledFootLockCache = false;
    this->FootLockRate = 0.00f;
    this->FootLockRateIncludingLandingRate = 0.00f;
}

