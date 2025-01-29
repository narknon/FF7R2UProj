#include "EndCrashBoxMiniGameGearBoxSkeletalMeshActor.h"

AEndCrashBoxMiniGameGearBoxSkeletalMeshActor::AEndCrashBoxMiniGameGearBoxSkeletalMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_BoxType = EEndCrashBoxMiniGameBoxType::GEAR;
    this->m_bHighGreadL = false;
    this->m_GroupIndex = 0;
    this->m_Radius = 0.00f;
    this->m_ImpulseStrength = 1500.00f;
    this->m_ImpulseRadius = 180.00f;
    this->m_BoxGimmickDifficultyType = EEndCrashBoxMiniGameGearBoxSkeletalMeshActorDifficultyType::ALL;
    this->m_LockCount = 0;
    this->m_Effect = NULL;
    this->m_EffectDummyPoint = NULL;
    this->HitSoundAsset = NULL;
}

void AEndCrashBoxMiniGameGearBoxSkeletalMeshActor::SetImpulseRadius(float InRadius) {
}

void AEndCrashBoxMiniGameGearBoxSkeletalMeshActor::SetEffectDummyPoint(EEndCrashBoxMiniGameGearBoxSkeletalMeshActorEffect Type, USceneComponent* Component) {
}

void AEndCrashBoxMiniGameGearBoxSkeletalMeshActor::PlayHitSe_TimerFunc() {
}

void AEndCrashBoxMiniGameGearBoxSkeletalMeshActor::OnEndImpulseInterval() {
}

void AEndCrashBoxMiniGameGearBoxSkeletalMeshActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}

bool AEndCrashBoxMiniGameGearBoxSkeletalMeshActor::IsElectricBox() {
    return false;
}

void AEndCrashBoxMiniGameGearBoxSkeletalMeshActor::Hit_TimerFunc() {
}

EEndCrashBoxMiniGameBoxType AEndCrashBoxMiniGameGearBoxSkeletalMeshActor::GetBoxType() {
    return EEndCrashBoxMiniGameBoxType::NORMAL;
}

void AEndCrashBoxMiniGameGearBoxSkeletalMeshActor::Deactive_TimerFunc() {
}


