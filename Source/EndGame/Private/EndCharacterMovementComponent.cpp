#include "EndCharacterMovementComponent.h"

UEndCharacterMovementComponent::UEndCharacterMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bComponentShouldUpdatePhysicsVolume = false;
    this->WalkableFloorZOnBattleNav = 0.02f;
}

void UEndCharacterMovementComponent::OnOverlapActor(AActor* InOverlapActor, bool bBeginOverlap) {
}


