#include "EndFieldEnemyTerritoryActor.h"

AEndFieldEnemyTerritoryActor::AEndFieldEnemyTerritoryActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->IsTerritoryActive = false;
    this->TerritoryType = EEndTerritoryType::Mob;
    this->UseDisableEscapeInvisibleWall = false;
    this->FloorCheckDistance = -1.00f;
    this->DisableEscapeInvisibleWall = NULL;
    this->DisableEscapeWallDiameter = 0.00f;
    this->TerritoryShape = EEndEnemyTerritoryShape::None;
    this->ForceValidLargeAria = false;
    this->ForceValidSmallAria = false;
    this->ForceValidSummonPoint = false;
}

void AEndFieldEnemyTerritoryActor::OnBeginDisableEscapeCollision(AActor* disableWall, AActor* Actor, FVector NormalImpulse, const FHitResult& Hit) {
}


