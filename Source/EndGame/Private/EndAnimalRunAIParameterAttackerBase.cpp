#include "EndAnimalRunAIParameterAttackerBase.h"

UEndAnimalRunAIParameterAttackerBase::UEndAnimalRunAIParameterAttackerBase() {
    this->bOverrideTargetSelectionPriorityList = false;
    this->bOverrideIsBallSelectDispersion = false;
    this->IsBallSelectDispersion = false;
    this->bOverrideBallSelectionType = false;
    this->BallSelectionType = EEndAnimalRunBallSelectionType::NearestSelf;
    this->bOverrideShootDistance = false;
    this->ShootDistance = 1600.00f;
    this->bOverrideShootDiffAngle = false;
    this->ShootDiffAngle = 120.00f;
    this->bOverrideShootDiffAngleBallToGoal = false;
    this->ShootDiffAngleBallToGoal = 120.00f;
    this->bOverrideRestTimeAfterShoot = false;
    this->RestTimeAfterShoot = 1.00f;
}


