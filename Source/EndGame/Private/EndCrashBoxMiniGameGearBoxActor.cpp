#include "EndCrashBoxMiniGameGearBoxActor.h"

AEndCrashBoxMiniGameGearBoxActor::AEndCrashBoxMiniGameGearBoxActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_BoxType = EEndCrashBoxMiniGameBoxType::GEAR;
    this->m_bHighGreadL = false;
    this->m_GroupIndex = 0;
    this->m_Radius = 0.00f;
    this->m_ImpulseStrength = 1500.00f;
    this->m_ImpulseRadius = 180.00f;
    this->m_BoxGimmickDifficultyType = EEndCrashBoxMiniGameGearBoxDifficultyType::ALL;
    this->m_LockCount = 0;
    this->m_Effect = NULL;
    this->m_EffectDummyPoint = NULL;
    this->HitSoundAsset = NULL;
}

void AEndCrashBoxMiniGameGearBoxActor::SetPoseableMeshComponent(UPoseableMeshComponent* _PoseableMeshComponent) {
}

void AEndCrashBoxMiniGameGearBoxActor::SetMaterialParameter(UMaterialParameterLightPlacedComponent* MaterialParameter) {
}

void AEndCrashBoxMiniGameGearBoxActor::SetImpulseRadius(float InRadius) {
}

void AEndCrashBoxMiniGameGearBoxActor::SetEffectDummyPoint(EEndCrashBoxMiniGameGearBoxEffect Type, USceneComponent* Component) {
}

void AEndCrashBoxMiniGameGearBoxActor::PlayHitSe_TimerFunc() {
}

void AEndCrashBoxMiniGameGearBoxActor::OnEndImpulseInterval() {
}

void AEndCrashBoxMiniGameGearBoxActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}

bool AEndCrashBoxMiniGameGearBoxActor::IsElectricBox() {
    return false;
}

void AEndCrashBoxMiniGameGearBoxActor::Hit_TimerFunc() {
}

EEndCrashBoxMiniGameBoxType AEndCrashBoxMiniGameGearBoxActor::GetBoxType() {
    return EEndCrashBoxMiniGameBoxType::NORMAL;
}

void AEndCrashBoxMiniGameGearBoxActor::Deactive_TimerFunc() {
}


