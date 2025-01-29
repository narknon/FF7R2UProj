#include "EndChocoboRaceBombBalloonActor.h"
#include "Components/SceneComponent.h"

AEndChocoboRaceBombBalloonActor::AEndChocoboRaceBombBalloonActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->BombClass = NULL;
    this->RespawnInterval = 2.00f;
    this->RespawnIntervalByNpc = 2.00f;
    this->AttackSpeed = 20.00f;
    this->AttackTurnSpeed = 180.00f;
    this->AttackInterval = 10.00f;
    this->ExplosionRadius = 1000.00f;
    this->SpawnWaitRange = 500.00f;
    this->GoBackSpeed = 15.00f;
    this->TargetExclusionTime = 20.00f;
}


