#include "EndBikeExpressionSteeringParameters.h"

FEndBikeExpressionSteeringParameters::FEndBikeExpressionSteeringParameters() {
    this->bEnableSteeringExpression = false;
    this->SteeringBoneName = EEndBikeBones::C_Body_a;
    this->SteeringRate = 0.00f;
    this->MaxAngle = 0.00f;
    this->InterpSpeed = 0.00f;
}

