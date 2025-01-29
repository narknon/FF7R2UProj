#include "EndInstancedLightweightPhysicsComponent.h"

UEndInstancedLightweightPhysicsComponent::UEndInstancedLightweightPhysicsComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->CastShadow = false;
    this->Radius = 5.00f;
    this->ReserveCount = 64;
    this->BoundTraceIntervalFrame = 1;
    this->BoundAttenuationMin = 0.35f;
    this->BoundAttenuationMax = 0.55f;
    this->BoundCountMax = 4;
    this->MaxBoundedDelayDestroyTime = 2.00f;
    this->GroundedStopSecnods = 1.00f;
    this->GroundedAdjustRotationSpeed = 10.00f;
    this->TraceIntervalSecondMin = 0.10f;
    this->DisableGravityHeightVelocityThreshold = 500.00f;
    this->HitSound = NULL;
}

void UEndInstancedLightweightPhysicsComponent::AddPhysicsInstance(const FTransform& Transform, const FVector& Impulse, float DelayTime, float LifeTime) {
}


