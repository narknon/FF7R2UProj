#include "EndCrashBoxMiniGameElectricCableActor.h"

AEndCrashBoxMiniGameElectricCableActor::AEndCrashBoxMiniGameElectricCableActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_CableType = EEndCrashBoxMiniGameCableType::A;
    this->m_GroupIndex = 0;
    this->m_CableGimmickDifficultyType = EEndCrashBoxMiniGameCableDifficultyType::ALL;
    this->m_Effect[0] = NULL;
    this->m_Effect[1] = NULL;
    this->m_Effect[2] = NULL;
    this->m_Effect[3] = NULL;
    this->m_Effect[4] = NULL;
    this->m_Effect[5] = NULL;
    this->m_Effect[6] = NULL;
    this->m_Effect[7] = NULL;
    this->m_Effect[8] = NULL;
    this->m_Effect[9] = NULL;
    this->m_Effect[10] = NULL;
    this->m_Effect[11] = NULL;
    this->m_Effect[12] = NULL;
    this->m_Effect[13] = NULL;
    this->m_Effect[14] = NULL;
    this->m_MainStaticMeshComponent = NULL;
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
    this->m_StaticMeshTriggerComponent[0] = NULL;
    this->m_StaticMeshTriggerComponent[1] = NULL;
    this->m_StaticMeshTriggerComponent[2] = NULL;
    this->m_StaticMeshTriggerComponent[3] = NULL;
    this->m_StaticMeshTriggerComponent[4] = NULL;
    this->m_StaticMeshTriggerComponent[5] = NULL;
    this->m_StaticMeshTriggerComponent[6] = NULL;
    this->m_StaticMeshTriggerComponent[7] = NULL;
    this->m_StaticMeshTriggerComponent[8] = NULL;
    this->m_StaticMeshTriggerComponent[9] = NULL;
    this->m_StaticMeshTriggerComponent[10] = NULL;
    this->m_EffectDummyPoint[0] = NULL;
    this->m_EffectDummyPoint[1] = NULL;
    this->m_EffectDummyPoint[2] = NULL;
    this->m_EffectDummyPoint[3] = NULL;
    this->m_EffectDummyPoint[4] = NULL;
    this->m_EffectDummyPoint[5] = NULL;
    this->m_EffectDummyPoint[6] = NULL;
    this->m_EffectDummyPoint[7] = NULL;
    this->m_EffectDummyPoint[8] = NULL;
    this->m_EffectDummyPoint[9] = NULL;
    this->m_EffectDummyPoint[10] = NULL;
    this->m_EffectDummyPoint[11] = NULL;
    this->m_EffectDummyPoint[12] = NULL;
    this->m_EffectDummyPoint[13] = NULL;
    this->m_EffectDummyPoint[14] = NULL;
}

void AEndCrashBoxMiniGameElectricCableActor::SetReferenceStaticMeshTrigger(EEndCrashBoxMiniGameCableType Type, UStaticMeshComponent* StaticMeshComp) {
}

void AEndCrashBoxMiniGameElectricCableActor::SetReferenceStaticMesh(EEndCrashBoxMiniGameCableType Type, UStaticMeshComponent* StaticMeshComp) {
}

void AEndCrashBoxMiniGameElectricCableActor::SetReferenceMainStaticMesh(UStaticMeshComponent* StaticMeshComp) {
}

void AEndCrashBoxMiniGameElectricCableActor::SetEffectDummyPoint(EEndCrashBoxMiniGameEffectCable Type, USceneComponent* Component) {
}

void AEndCrashBoxMiniGameElectricCableActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}

EEndCrashBoxMiniGameCableType AEndCrashBoxMiniGameElectricCableActor::GetBoxType() {
    return EEndCrashBoxMiniGameCableType::A;
}

EEndCrashBoxMiniGameCableType AEndCrashBoxMiniGameElectricCableActor::ApplyCableType() {
    return EEndCrashBoxMiniGameCableType::A;
}


