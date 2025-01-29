#include "EndFrogGuysTriggerComponent.h"

UEndFrogGuysTriggerComponent::UEndFrogGuysTriggerComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bForceJump = false;
    this->JumpVelocity = 2000.00f;
    this->JumpGravityScale = 1.00f;
    this->bIsToKnockback = false;
    this->bIsCircularKnockback = false;
    this->KnockbackPitch = 45.00f;
    this->KnockbackSpeed = 2000.00f;
    this->KnockbackGravityScale = 0.50f;
    this->bIsToApplyUpwardsForce = false;
    this->UpwardsForce = 60000.00f;
    this->UpwardsForceSlowdownHeightRatio = 0.50f;
    this->bIsToWarpToCheckpoint = false;
    this->bIsCheckpoint = false;
    this->CheckpointPriority = 0;
    this->bIsConveyor = false;
    this->bIsAIShouldJump = false;
    this->bIsAIJumpApproach = false;
    this->PCHitSound = NULL;
    this->NPCHitSound = NULL;
}

void UEndFrogGuysTriggerComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}

void UEndFrogGuysTriggerComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}


