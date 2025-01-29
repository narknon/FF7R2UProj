#include "EndCardGame3DToken.h"
#include "GameFramework/ProjectileMovementComponent.h"

AEndCardGame3DToken::AEndCardGame3DToken(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
    this->bPlayer = false;
    this->LaneIndex = 0;
    this->KillZ = 0.00f;
    this->bPlayBoundSound = true;
    this->MoveState = EEndCardGame3DTokenMoveState::None;
}

void AEndCardGame3DToken::OnProjectileStop(const FHitResult& HitResult) {
}


