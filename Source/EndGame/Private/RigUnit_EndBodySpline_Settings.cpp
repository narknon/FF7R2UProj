#include "RigUnit_EndBodySpline_Settings.h"

FRigUnit_EndBodySpline_Settings::FRigUnit_EndBodySpline_Settings() {
    this->PointHistoryLifeTime = 0.00f;
    this->PointPredictionDistanceStep = 0.00f;
    this->BlendInSpeed = 0.00f;
    this->BlendOutSpeed = 0.00f;
    this->RotationInterpSpeed = 0.00f;
    this->NoDesiredMovementContinuationTime = 0.00f;
    this->bIgnoreWalkRunStart = false;
}

