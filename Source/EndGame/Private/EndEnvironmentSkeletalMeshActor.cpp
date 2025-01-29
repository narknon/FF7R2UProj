#include "EndEnvironmentSkeletalMeshActor.h"

AEndEnvironmentSkeletalMeshActor::AEndEnvironmentSkeletalMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bHiddenUpdatedLoopAnimation = false;
    this->bHighPriorityLocationAssetUserDataAnimation = false;
    this->SoundBank = NULL;
    this->bActiveOverlap = false;
    this->bInitAsPhysicsObject = false;
    this->bAutoResetPlacement = false;
    this->PhysicsObjectCollisionPresetType = EEndPhysicsStaticMeshCollisionPresetType::AffectCharacterMove;
    this->NearFadeType = EEndEnvironmentNearFadeType::DisableFade;
    this->OverwriteNearFadeDistance = -1.00f;
    this->OverwriteNearFadeDistanceOnBattle = -1.00f;
    this->bCanSkillCameraDitherFade = false;
    this->PrecomputedLightEnvironmentBlendBoneType = EEndEnvironmentPrecomputedLightEnvironmentBlendBoneType::Rotation;
    this->bUsePrecomputedLightEnvironmentBlendBoneAxisRangeSwing = false;
}

void AEndEnvironmentSkeletalMeshActor::OnComponentPhysicsHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}


