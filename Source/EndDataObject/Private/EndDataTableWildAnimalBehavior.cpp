#include "EndDataTableWildAnimalBehavior.h"

FEndDataTableWildAnimalBehavior::FEndDataTableWildAnimalBehavior() {
    this->IdleSelectWeight = 0;
    this->IdleContinueCountMax = 0;
    this->IdleTime = 0.00f;
    this->AdditionalIdleTime = 0.00f;
    this->WanderingSelectWeight = 0;
    this->WanderingContinueCountMax = 0;
    this->WanderingTime = 0.00f;
    this->AdditionalWanderingTime = 0.00f;
    this->WanderingType = 0;
    this->WanderingRadius = 0.00f;
    this->SplinePositionDistanceMin = 0.00f;
    this->SplinePositionDistanceMax = 0.00f;
    this->BaseMoveSpeedScale = 0.00f;
    this->RotationRateScaleMin = 0.00f;
    this->RotationRateScaleMax = 0.00f;
    this->VisibleAngle = 0.00f;
    this->SenseNPC = 0;
    this->SpacingDistance = 0.00f;
    this->FixedHeightOffset = 0.00f;
    this->RandomHeightOffset = 0.00f;
    this->BeginCautionEnterRadius = 0.00f;
    this->EndCautionExitRadius = 0.00f;
    this->AvoidCount = 0;
    this->AvoidRadius = 0.00f;
    this->BeginEscapeEnterRadius = 0.00f;
    this->EscapeTimeOut = 0.00f;
    this->EscapeHideOnOutCameraGraceTime = 0.00f;
    this->EscapeType = 0;
    this->SpacingDistanceOnEscape = 0.00f;
    this->TurnOnEscape = 0;
    this->TurnOnEscapePlayRateMin = 0.00f;
    this->TurnOnEscapePlayRateMax = 0.00f;
    this->NoCollisionOnEscape = 0;
    this->FlyOnEscape = 0;
    this->BeginEscapeMotionPlayRateMin = 0.00f;
    this->BeginEscapeMotionPlayRateMax = 0.00f;
    this->LandingOnEscape = 0;
    this->EscapeDelayTimeMin = 0.00f;
    this->EscapeDelayTimeMax = 0.00f;
    this->HideDelayTimeInMotion = 0.00f;
}

