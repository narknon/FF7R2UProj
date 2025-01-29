#include "EndAnimalRunManagerActor.h"

AEndAnimalRunManagerActor::AEndAnimalRunManagerActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->InitScore = 5;
    this->FinishCondition = EAnimalFinishCondition::TimeUp;
    this->SpawnBallDispersion = 80.00f;
    this->JumpForwardVelocityRate = 1.50f;
    this->JumpZVelocity = 1500.00f;
    this->JumpAttackVeloctyRate = 0.40f;
    this->BallLiftPower = 400.00f;
    this->BallLiftForwardPower = 400.00f;
    this->BallShootPower = 800.00f;
    this->BallJumpShootPower = 2000.00f;
    this->BallDropShootForwardPower = 800.00f;
    this->BallDropShootDownPower = 800.00f;
    this->ToleranceDist2Ball = 400.00f;
    this->ToleranceDist2BallLift = 400.00f;
    this->ToleranceDist2BallJump = 400.00f;
    this->ToleranceDist2BallDrop = 400.00f;
    this->DashOffsetRate = 1.30f;
    this->SpeedForDamageAddReaction = 1000.00f;
    this->SpeedForDamageReaction = 2000.00f;
    this->SuperDashJudgeCount = 5;
    this->DashSwitchingInactivePeriod = 10;
    this->RotationRateScale = 1.50f;
    this->TargetBallDistance = 300.00f;
    this->TargetBallAngle = 60.00f;
    this->ShootingCorrectionDistance = 1500.00f;
    this->ShootingCorrectionAngle = 30.00f;
    this->ShootingCorrectionRate = 0.30f;
    this->AIDirectorClass = NULL;
}


