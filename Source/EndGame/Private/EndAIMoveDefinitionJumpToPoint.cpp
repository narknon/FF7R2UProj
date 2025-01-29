#include "EndAIMoveDefinitionJumpToPoint.h"

UEndAIMoveDefinitionJumpToPoint::UEndAIMoveDefinitionJumpToPoint() {
    this->PointSelectType = EEndAIEnemyPointSelectType::DistanceMin;
    this->bTurnToJump = false;
    this->bWall = false;
    this->bForceJump = false;
}


