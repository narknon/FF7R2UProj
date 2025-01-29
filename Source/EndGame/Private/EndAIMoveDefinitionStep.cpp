#include "EndAIMoveDefinitionStep.h"

UEndAIMoveDefinitionStep::UEndAIMoveDefinitionStep() {
    this->bNotActionInterrupt = true;
    this->DirctionType = EEndAIMoveDefinitionStepDirction::None;
    this->MoveDistance = 400.00f;
    this->bTraceWall = true;
    this->bCheckBattleArea = true;
    this->Speed = 1500.00f;
    this->bAroundStep = false;
    this->bSelfDircStep = false;
    this->PlayStartTime = 0.00f;
    this->bDrawDebug = false;
}


