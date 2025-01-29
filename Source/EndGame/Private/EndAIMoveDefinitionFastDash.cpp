#include "EndAIMoveDefinitionFastDash.h"

UEndAIMoveDefinitionFastDash::UEndAIMoveDefinitionFastDash() {
    this->bNotActionInterrupt = true;
    this->GotoType = EEndAIMoveDefinitionFastDashGotoType::TargetCharacter;
    this->bCanPreTurn = false;
    this->RotationRate = 0.00f;
    this->bUpdateGoalLocation = false;
    this->FastMoveSpeed = 0.00f;
    this->MissingDistance = 0.00f;
    this->MarginDistance = 0.00f;
    this->LimitTime = 0.00f;
    this->bMoveToNextGotoOffsetByHitWall = false;
    this->MoveFriction = 0.00f;
    this->bDisableMoveFriction = false;
    this->bDrawTargetPoint = false;
    this->bIgnoreHeight = false;
    this->ActionExecuteType = EEndAIMoveDefinitionFastDashActionExecuteType::Always;
}


