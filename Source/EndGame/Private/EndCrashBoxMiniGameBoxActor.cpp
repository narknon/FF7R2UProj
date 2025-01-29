#include "EndCrashBoxMiniGameBoxActor.h"

AEndCrashBoxMiniGameBoxActor::AEndCrashBoxMiniGameBoxActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanBeInCluster = false;
    this->BonusBoxClass = NULL;
    this->m_BoxType = EEndCrashBoxMiniGameBoxType::NORMAL;
    this->m_bHighGreadL = false;
    this->m_GroupIndex = 0;
    this->m_Radius = 0.00f;
    this->m_ImpulseStrength = 500.00f;
    this->m_ImpulseRadius = 60.00f;
    this->m_BoxGimmickDifficultyType = EEndCrashBoxMiniGameBoxDifficultyType::ALL;
    this->m_bPhysicalMagic = false;
    this->m_BonusBoxCount = 0;
    this->m_Effect[0] = NULL;
    this->m_Effect[1] = NULL;
    this->m_StaticMeshComponent[0] = NULL;
    this->m_StaticMeshComponent[1] = NULL;
    this->m_StaticMeshComponent[2] = NULL;
    this->m_StaticMeshComponent[3] = NULL;
    this->m_StaticMeshComponent[4] = NULL;
    this->m_StaticMeshComponent[5] = NULL;
    this->m_StaticMeshComponent[6] = NULL;
    this->m_StaticMeshComponent[7] = NULL;
    this->m_StaticMeshComponent[8] = NULL;
    this->m_StaticMeshComponent[9] = NULL;
    this->m_StaticMeshComponent[10] = NULL;
    this->m_StaticMeshComponent[11] = NULL;
    this->m_StaticMeshComponent[12] = NULL;
    this->m_EffectDummyPoint[0] = NULL;
    this->m_EffectDummyPoint[1] = NULL;
    this->m_EnemyTerritoryId = 0;
    this->HitSoundAsset = NULL;
}

void AEndCrashBoxMiniGameBoxActor::SetReferenceStaticMesh(EEndCrashBoxMiniGameBoxType Type, UStaticMeshComponent* StaticMeshComp) {
}

void AEndCrashBoxMiniGameBoxActor::SetMaterialParameter(UMaterialParameterLightPlacedComponent* MaterialParameter) {
}

void AEndCrashBoxMiniGameBoxActor::SetImpulseRadius(float InRadius) {
}

void AEndCrashBoxMiniGameBoxActor::SetEffectDummyPoint(EEndCrashBoxMiniGameEffect Type, USceneComponent* Component) {
}

void AEndCrashBoxMiniGameBoxActor::SetBonusBoxEmissiveMaterial_Implementation() {
}

void AEndCrashBoxMiniGameBoxActor::PlayHitSe_TimerFunc() {
}

void AEndCrashBoxMiniGameBoxActor::OnEndImpulseInterval() {
}

void AEndCrashBoxMiniGameBoxActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}

bool AEndCrashBoxMiniGameBoxActor::IsElectricBox() {
    return false;
}

void AEndCrashBoxMiniGameBoxActor::Hit_TimerFunc() {
}

EEndCrashBoxMiniGameBoxType AEndCrashBoxMiniGameBoxActor::GetBoxType() {
    return EEndCrashBoxMiniGameBoxType::NORMAL;
}

void AEndCrashBoxMiniGameBoxActor::Deactive_TimerFunc() {
}

EEndCrashBoxMiniGameBoxType AEndCrashBoxMiniGameBoxActor::ApplyBoxType() {
    return EEndCrashBoxMiniGameBoxType::NORMAL;
}


