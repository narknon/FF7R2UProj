#include "EndChocoboWaterJetActionParam.h"

UEndChocoboWaterJetActionParam::UEndChocoboWaterJetActionParam() {
    this->JumpGravityScale = 7.00f;
    this->JumpVelocityZ = 1800.00f;
    this->JumpVelocityXY = 1500.00f;
    this->MaxSpeed = 100.00f;
    this->MinSpeed = 0.00f;
    this->Acceleration = 30.00f;
    this->Deceleration = 30.00f;
    this->SpeedReduction = 20.00f;
    this->BackwardAngleLimit = 150.00f;
    this->YawMaxSpeed = 60.00f;
    this->YawAcceleration = 1000.00f;
    this->YawConstantArrivalTime = 0.10f;
    this->MaxUpStreamHeight = 5000.00f;
    this->UpStreamHeightOnGround = 300.00f;
    this->UpStreamAccelerationOnZUp = 10.00f;
    this->UpStreamAccelerationOnZDown = 30.00f;
    this->UpStreamAccelerationOnZUpOnGround = 100.00f;
    this->UpStreamAccelerationOnZDownOnGround = 100.00f;
    this->MaxUpstreamSpeed = 20.00f;
    this->ConstantArrivalTime = 0.10f;
    this->ConstantArrivalTimeOnGround = 0.05f;
    this->UpstreamGravityScale = 0.00f;
    this->DecendingGravityScale = 2.00f;
    this->DecendingMaxSpeed = 36.00f;
    this->MaxSpeedOnDash = 100.00f;
    this->AccelerationOnDash = 30.00f;
    this->DecelerationOnDash = 30.00f;
    this->DecendingGravityScaleOnDash = 2.00f;
    this->DecendingMaxSpeedOnDash = 36.00f;
    this->DecendingGravityScaleOnDashOnGround = 2.00f;
    this->DecendingMaxSpeedOnDashOnGround = 36.00f;
    this->bUseMaxHeightAbsoluteZ = true;
    this->BaseHeightOfMaxHeigth = 0.00f;
    this->MaxJetGauge = 100.00f;
    this->JetGaugeIncreaseInitialValue = 10.00f;
    this->JetGaugeIncreaseGradient = 1.00f;
    this->JetGaugeDecreaseTypeA = 30.00f;
    this->JetGaugeDecreaseOnGround = 30.00f;
    this->OverheatDecendingGravityScale = 1.00f;
    this->OverheatDecendingMaxSpeed = 36.00f;
    this->EffectDelayTimeOnJumpRising = 0.10f;
    this->MaxRollAngle = 10.00f;
    this->InvalidNextBeginJetTime = 1.00f;
    this->AutoMoveOverNavMeshMaxCheckDistance = 1000.00f;
    this->HitStopScaleOnGetChocoboGrass = 0.05f;
    this->HitStopTimeOnGetChocoboGrass = 0.30f;
}


