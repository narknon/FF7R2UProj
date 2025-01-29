#include "EndChocoboAirGlideActionParam.h"

UEndChocoboAirGlideActionParam::UEndChocoboAirGlideActionParam() {
    this->JumpGravityScale = 7.00f;
    this->JumpVelocityZ = 1800.00f;
    this->JumpVelocityXY = 1500.00f;
    this->GlideGravityScale = 0.10f;
    this->GlideGravityScaleUpward = 1.00f;
    this->MaxSpeed = 100.00f;
    this->MaxSpeedXYOnDive = 100.00f;
    this->MaxSpeedXYOnRaise = 100.00f;
    this->Acceleration = 30.00f;
    this->Deceleration = 30.00f;
    this->MotionBlendSpeedX = 1.00f;
    this->MotionBlendSpeedY = 1.00f;
    this->YawMaxSpeed = 60.00f;
    this->TerminalVelocityOnGlide = 37.00f;
    this->AccelerationForRecoveryTerminalVelocity = 100.00f;
    this->GravityScaleForRecoveryTerminalVelocity = 2.00f;
    this->HeightLimitSmoothingConstantArrivalTime = 0.10f;
    this->MinInputThreshold = 0.10f;
    this->KeepDiveOrRaiseThresholdTime = 0.50f;
    this->MaxPitchAngleScaleInUpdraftVolume = 1.00f;
    this->MaxPitchAngleScaleOnRaise = 1.00f;
    this->MaxYawSpeedCoverageTime = 1.00f;
    this->MaxRollAngle = 30.00f;
    this->MaxGravityScaleOnDive = 0.00f;
    this->MaxTerminalVelocityOnDive = 0.00f;
    this->EnableRaiseTimer = 2.00f;
    this->AcceptRaiseTime = 1.00f;
    this->RaiseHeightAddOffset = 10.00f;
    this->CameraPitchOffset = -10.00f;
    this->CameraPitchOffsetOnDive = 0.00f;
    this->CameraPitchOffsetOnRaise = 0.00f;
    this->CameraPitchOffsetInUpdraft = 10.00f;
    this->bEnableMotionSensor = true;
    this->MotionSensorMaxPitch = 60.00f;
    this->bEnableWindBreakOnRaise = false;
    this->MinSpeed = 20.00f;
    this->BackwardAngleLimit = 150.00f;
    this->YawAcceleration = 1000.00f;
    this->YawConstantArrivalTime = 0.10f;
    this->bEnableYawSpeedConstant = false;
    this->YawMaxSpeedConstant = 1.00f;
    this->CameraMaxAimOffsetForward = 0.00f;
    this->CameraMaxAimOffsetRight = 0.00f;
}


