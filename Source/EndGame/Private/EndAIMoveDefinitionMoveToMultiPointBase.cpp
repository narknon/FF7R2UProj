#include "EndAIMoveDefinitionMoveToMultiPointBase.h"

UEndAIMoveDefinitionMoveToMultiPointBase::UEndAIMoveDefinitionMoveToMultiPointBase() {
    this->PointSelectType = EEndAIEnemyPointSelectType::DistanceMin;
    this->RotationRateScale = 1.00f;
    this->GoalRadius = 0.00f;
    this->bDisableMoveOnlyNavMesh = false;
}


