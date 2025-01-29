#include "EndSmoothTerrainCollisionVolume.h"
#include "Components/BoxComponent.h"
#include "EndSmoothTerrainCollisionComponent.h"

AEndSmoothTerrainCollisionVolume::AEndSmoothTerrainCollisionVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    this->MaxClimbHeight = 30.00f;
    this->MinSlopeDiffDegrees = 20.00f;
    this->MinDebugDrawSlopeDiffDegrees = 5.00f;
    this->BoxComponent = (UBoxComponent*)RootComponent;
    this->CollisionComponent = CreateDefaultSubobject<UEndSmoothTerrainCollisionComponent>(TEXT("CollisionComponent"));
    this->TempBodySetup = NULL;
    this->CollisionComponent->SetupAttachment(RootComponent);
}


