#include "EndBikeWheeledMovementSetting.h"

UEndBikeWheeledMovementSetting::UEndBikeWheeledMovementSetting() {
    this->ForwardMaxSpeed = 180.00f;
    this->BackwardMaxSpeed = 0.00f;
    this->ForwardMinSpeed = 60.00f;
    this->MaxYawAngleAlongSpline = 60.00f;
    this->MaxYawAngleAlongSplineOnWalll = 40.00f;
    this->YawAngleCoverageTimeAlongSpline = 0.50f;
    this->MaxRollForBlendInput = 30.00f;
    this->MaxAddRunBlendValueOnMaxSpeed = 0.70f;
    this->MaxTurningRadius = 80.00f;
    this->MinTurningRadius = 30.00f;
    this->InputSteeringInterpSpeed = 20.00f;
    this->NeutralFrictionScaleOnGuard = 1.00f;
    this->OverSteerFrictionScaleOnGuard = 1.00f;
    this->NeutralFrictionScaleOnDamage1 = 1.00f;
    this->NeutralFrictionScaleOnDamage2 = 1.00f;
    this->NeutralFrictionScaleOnContact = 1.00f;
    this->OverSteerFrictionScaleOnContact = 1.00f;
    this->FrontWheelOffset = 50.00f;
    this->RearWheelOffset = -50.00f;
    this->SamplingOffsetForSplineTurningRadius = 5000.00f;
    this->MinSplineTurningRadius = 17000.00f;
    this->MaxRoll = 30.00f;
    this->bResetRollSpeedOnNoInput = true;
    this->bResetRollSpeedOnSwitchInput = true;
    this->ContactWallContinuousTime = 0.20f;
    this->bEnableOverSteer = false;
    this->BeginOverSteerSpeed = 100.00f;
    this->EndOverSteerSpeed = 80.00f;
    this->EndOverSteerReleaseInputTime = 3.00f;
    this->EndOverSteerContactAngle = 30.00f;
    this->OverSteerSlipAngle = 20.00f;
    this->FrontWheelOffsetForClimbing = 0.00f;
    this->RearWheelOffsetForClimbing = 0.00f;
    this->RightSideWheelOffsetForClimbing = 0.00f;
    this->ConstArrivalTimeForLimitJumpOverWall = 0.10f;
    this->ClimbingLimitHeightFromWallTop = 30.00f;
    this->MaxPitchOnClimbing = 30.00f;
    this->MinPitchOnClimbing = -20.00f;
    this->MinSpeedOnStartClimbingKph = 50.00f;
    this->MinSpeedOnClimbingKph = 60.00f;
    this->DeltaSpeedToMinPitchOnClimbing = 30.00f;
    this->CentrifugalForceMinusBias = 0.80f;
    this->MaxFallSpeedOnWallClimbing = -30.00f;
    this->BoostItemAddSpeed = 60.00f;
    this->BoostItemAddAccel = 60.00f;
    this->BoostItemApplyTime = 4.00f;
    this->StartAccelScale = 5.00f;
    this->StartAccelSetScaleTime = 2.00f;
    this->GoalMinSpeedKphWithMotion = 120.00f;
    this->GoalLimitLane = 1000.00f;
    this->DisableSpawnEnemyCondition_Speed = 100.00f;
    this->DisableSpawnEnemyCondition_Time = 10.00f;
    this->bEnableNewVersion = false;
    this->BrakeScaleOnGoal = 1.20f;
    this->LimitSpeedFrictionScaleOnGoal = 100.00f;
    this->LookAtLimitAngleDefault = 180.00f;
    this->LookAtLimitAngleOnClimbWall = 70.00f;
    this->LookAtLimitAngleOnBoost = 100.00f;
    this->LookAtLimitAngleOnBoostAndClimbWall = 70.00f;
}


