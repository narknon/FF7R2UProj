#include "EndChocoboCommonActionParam.h"

UEndChocoboCommonActionParam::UEndChocoboCommonActionParam() {
    this->FieldStepMoveDistance = 800.00f;
    this->FieldStepSpeed = 150.00f;
    this->FieldDriftInitialSpeedRate = 0.50f;
    this->FieldDriftInitialMinSpeed = 80.00f;
    this->FieldDriftDeceleration = 1.00f;
    this->FieldDriftMinSpeed = 80.00f;
    this->FieldDriftMinTime = 3.00f;
    this->FieldDriftDisableTime = 0.50f;
    this->bFieldDriftInputVectorAlongCamera = true;
    this->FieldDriftInputMaxAngle = 70.00f;
    this->FieldDriftYawPoseOffset = 15.00f;
    this->FieldDriftForwardAngleLimit = 15.00f;
    this->bFieldBrakeActionEnable = false;
    this->FieldBrakeBeginWalkStopSpeed = 20.00f;
    this->FieldBrakeBeginBrakeActionSpeed = 45.00f;
    this->FieldBrakeBeginBrakeFinishMotion = 60.00f;
    this->Acceleration = 20.00f;
    this->Deceleration = 50.00f;
    this->InputYawDeltaLimitAngle = 160.00f;
    this->DashToRunTime = 0.25f;
    this->bEnableWalkRunTurn = false;
    this->KeepDashTimeWhenInheritFromPlayer = 1.00f;
    this->TargetSpeedRateWhenInheritFromPlayer = 0.50f;
    this->IgnoreInputOnRideWhenIdle = 0.20f;
    this->bEnableJumpGetOff = false;
    this->JumpGetOffCondition = EEndChocoboPlayerMoveState::Run;
    this->bDashOffWhenCrashed = true;
    this->DirectRideWithInputDistance = 300.00f;
    this->DirectRideWithInputDistanceOnSwim = 200.00f;
    this->DirectRideWithInputMaxYaw = 30.00f;
    this->DirectRideWithInputMinPower = 0.30f;
    this->DecelerationTimeOnGetOff = 0.50f;
    this->FieldBrakeMaxSpeedOnDisableInput = 30.00f;
    this->FieldBrakePowerScaleOnDisableInput = 20.00f;
}


