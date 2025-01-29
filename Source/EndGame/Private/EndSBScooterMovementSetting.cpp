#include "EndSBScooterMovementSetting.h"

UEndSBScooterMovementSetting::UEndSBScooterMovementSetting() {
    this->ForwardMaxSpeed = 80.00f;
    this->ForwardAccel = 30.00f;
    this->ForwardBrake = 60.00f;
    this->NeutralFriction = 20.00f;
    this->MaxTurningRadius = 10.00f;
    this->MinTurningRadius = 0.50f;
    this->AngulerSpeedOnTurningRadiusZero = 20.00f;
    this->YawAngleCoverageTimeForInputVectorOnly = 0.05f;
    this->MaxStepHeight = 30.00f;
    this->SpeedRateByTurningRadiusInputThreshhold = 0.01f;
    this->SteeringMaxSideInput = 0.90f;
    this->SteeringMaxSidePendingTime = 2.00f;
    this->SteeringMaxSideBlendTime = 0.50f;
    this->SteeringMaxSideLxAngleRange = 30.00f;
    this->SteeringMaxSideMinSpeed = 15.00f;
    this->LimitNormalLength = 500.00f;
    this->MaxLimitSteeringDistance = 1000.00f;
    this->BeginForceSteeringTime = 1.00f;
    this->MaxSpeedInArea = 20.00f;
    this->MaxLimitSpeedDistance = 2000.00f;
    this->BeginForceSpeedTime = 1.00f;
    this->LimitSpeedOnCollisionKph = 20.00f;
    this->bEnableDirectRide = true;
    this->DirectRideWithInputDistance = 200.00f;
    this->DirectRideWithInputMaxYaw = 30.00f;
    this->DirectRideWithInputMinPower = 0.30f;
    this->InvalideAutoRideTimer = 1.00f;
    this->PhyObjBreakableSpeedKph = 20.00f;
    this->BeginLoopVibration = 0.50f;
    this->BeginHitVibrationSpeed = 20.00f;
    this->BackwardMaxSpeedRate = 0.25f;
    this->MinSpeedForSteeringToLimit = 20.00f;
}


