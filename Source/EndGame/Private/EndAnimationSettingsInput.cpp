#include "EndAnimationSettingsInput.h"

FEndAnimationSettingsInput::FEndAnimationSettingsInput() {
    this->IdleToWalkInputThreshold = 0.00f;
    this->WalkToRunInputThreshold = 0.00f;
    this->HighWalkMovementInputValue = 0.00f;
    this->JogMovementInputValue = 0.00f;
    this->RunMovementInputValue = 0.00f;
    this->DashMovementInputValue = 0.00f;
    this->InputDurationThreshold = 0.00f;
    this->HighSpeedInterpWalkRunInputTime = 0.00f;
    this->HighSpeedInterpWalkRunBlendInputSpeedBias = 0.00f;
    this->BlendInputSpeedInterpSpeedUpper = 0.00f;
    this->BlendInputSpeedInterpSpeedLower = 0.00f;
    this->BlendInputSpeedInterpSpeedUpperAI = 0.00f;
    this->BlendInputSpeedInterpSpeedLowerAI = 0.00f;
    this->BlendInputDirectionInterpSpeed = 0.00f;
    this->AccelTurnInputSizeThreshold = 0.00f;
    this->AccelTurnInputAngleThreshold = 0.00f;
    this->AccelTurnInputTimeMax = 0.00f;
    this->RotationRateInterpSpeed = 0.00f;
    this->ForceZeroSetAccelStartRotationRateInputAngleThreshold = 0.00f;
    this->AccelStartCancelTurnTimeThreshold = 0.00f;
    this->SlopeWalkRestrictionAngleThreshold = 0.00f;
    this->Direction90_MaxThreshold_0 = 0.00f;
    this->Direction90_MaxThreshold_90 = 0.00f;
    this->Direction45_MaxThreshold_0 = 0.00f;
    this->Direction45_MaxThreshold_45 = 0.00f;
    this->Direction45_MaxThreshold_90 = 0.00f;
    this->Direction45_MaxThreshold_135 = 0.00f;
}

