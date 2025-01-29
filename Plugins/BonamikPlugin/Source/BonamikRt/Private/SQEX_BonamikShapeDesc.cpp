#include "SQEX_BonamikShapeDesc.h"

FSQEX_BonamikShapeDesc::FSQEX_BonamikShapeDesc() {
    this->mShapeId = 0;
    this->mPlaneThickness = 0.00f;
    this->mPlaneOffset = 0.00f;
    this->mCapsuleConcaveRatio = 0.00f;
    this->bIsInverse = false;
    this->bIsInfinity = false;
    this->bResampleStart = false;
}

