#include "EndAIMoveDefinitionWarpToPoint.h"

UEndAIMoveDefinitionWarpToPoint::UEndAIMoveDefinitionWarpToPoint() {
    this->PointSelectType = EEndAIEnemyPointSelectType::DistanceMin;
    this->bUseReservePoint = false;
    this->bCheckWarpNearActor = false;
    this->CheckWarpNearActorDist = 200.00f;
    this->bUseTargetPointRotation = false;
    this->bCanWarpNearPoint = false;
}


