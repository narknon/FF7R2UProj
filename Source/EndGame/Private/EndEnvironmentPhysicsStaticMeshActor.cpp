#include "EndEnvironmentPhysicsStaticMeshActor.h"

AEndEnvironmentPhysicsStaticMeshActor::AEndEnvironmentPhysicsStaticMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PhysicsBehavior = EEndPhysicsStaticMeshResponse::Default;
    this->InitialDisableMask = EDisableSimulatePhysicsMask::SP_Max;
    this->ParentCollisionPresetType = EEndPhysicsStaticMeshCollisionPresetType::AffectCharacterMove;
    this->PartsCollisionPresetType = EEndPhysicsStaticMeshCollisionPresetType::NotAffectCharacterMove;
    this->bIsToAutoSetPartsMass = true;
    this->bEnabledWaterBuoyancy = true;
    this->bSpawnInWater = false;
    this->PartsMassScale = 0.10f;
    this->PartsOverrideMass = 0.50f;
    this->PartsMaxDepenetrationVelocity = -1.00f;
    this->BuoyancyWaterDepthOffset = 0.00f;
    this->PartsDestroyRate = 0;
    this->DefaultPartsFadeOutTime = 5.00f;
    this->bSteeringObstacle = false;
    this->bNeverBreakOnThrow = false;
    this->bIsToOverlapTriggersAfterFirstHit = false;
    this->bEnableDamageSourceLaserBlock = false;
    this->bEnabledWorldCollisionStableCheck = true;
    this->bEnableAutoDestroyAfterBreak = false;
    this->DefaultAutoDestroyTime = 5.00f;
    this->VehicleBreakableSpeedType = EEndEnvironmentPhysHitBreakSpeed::Speed0;
    this->bEnablePhysActorHit = false;
    this->bAutoResetPlacement = false;
    this->EffectPack = NULL;
    this->BreakEffectPosition = EEnvEffectGeneratePosition::None;
    this->BoundEffectPosition = EEnvEffectGeneratePosition::None;
    this->BoundEffectRequireImpuctSize = 200.00f;
    this->bCanBeHeldByFatMoogle = false;
}

void AEndEnvironmentPhysicsStaticMeshActor::OnEndImpulseInterval() {
}

void AEndEnvironmentPhysicsStaticMeshActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}

void AEndEnvironmentPhysicsStaticMeshActor::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}

void AEndEnvironmentPhysicsStaticMeshActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}



