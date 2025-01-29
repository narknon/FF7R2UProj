#include "EndFieldMovementComponent.h"

UEndFieldMovementComponent::UEndFieldMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->InitialSpeed = 0.00f;
    this->MaxSpeed = 0.00f;
    this->bOnlyMoveOnFloor = true;
    this->bInitialVelocityInLocalSpace = true;
    this->bForceSubStepping = false;
    this->bSimulationEnabled = true;
    this->bSweepCollision = true;
    this->bBounceAngleAffectsFriction = false;
    this->bIsSliding = false;
    this->PreviousHitTime = 1.00f;
    this->ProjectileGravityScale = 4.00f;
    this->Buoyancy = 0.00f;
    this->Bounciness = 0.60f;
    this->HitFriction = 0.20f;
    this->BounceVelocityStopSimulatingThreshold = 5.00f;
    this->MinFrictionFraction = 0.00f;
    this->FrictionPer60Fps = 0.00f;
    this->MaxSimulationTimeStep = 0.05f;
    this->MaxSimulationIterations = 4;
    this->BounceAdditionalIterations = 1;
}

void UEndFieldMovementComponent::SetVelocityInLocalSpace(FVector NewVelocity) {
}

FVector UEndFieldMovementComponent::LimitVelocity(FVector NewVelocity) const {
    return FVector{};
}


