#include "EndAIMoveDefinitionConfrontBase.h"

UEndAIMoveDefinitionConfrontBase::UEndAIMoveDefinitionConfrontBase() {
    this->bTurnToMove = false;
    this->TurnToMoveAngle = 90.00f;
    this->TurnToMoveTurnTolerance = 45.00f;
    this->bImmediateNoPathMove = false;
    this->bDisablePathFind_Approach = false;
    this->RotationRateScale = 1.00f;
    this->ExecType = EEndAIMoveDefinitionStepExecType::None;
    this->StepProbability = 50;
    this->StepCoolTime = 15.00f;
    this->StepCoolTimeInit = 10.00f;
}


