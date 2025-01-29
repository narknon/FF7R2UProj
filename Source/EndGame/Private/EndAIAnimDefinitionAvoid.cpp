#include "EndAIAnimDefinitionAvoid.h"

UEndAIAnimDefinitionAvoid::UEndAIAnimDefinitionAvoid() {
    this->DirctionType = EEndAIMoveDefinitionStepDirction::None;
    this->MoveDistance = 400.00f;
    this->bTraceWall = true;
    this->bCheckBattleArea = true;
    this->bDrawDebug = false;
}


