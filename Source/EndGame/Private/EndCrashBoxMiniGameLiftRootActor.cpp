#include "EndCrashBoxMiniGameLiftRootActor.h"

AEndCrashBoxMiniGameLiftRootActor::AEndCrashBoxMiniGameLiftRootActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanBeInCluster = false;
    this->LiftClass = NULL;
    this->DownLiftClass = NULL;
    this->LeverClass = NULL;
    this->m_GroupIndex = 0;
    this->m_StaticMeshComponent[0] = NULL;
    this->m_StaticMeshComponent[1] = NULL;
    this->m_StaticMeshComponent[2] = NULL;
    this->m_StaticMeshComponent[3] = NULL;
    this->m_StaticMeshComponent[4] = NULL;
    this->m_bStartUpSide = false;
    this->m_bLiftLongMove = false;
    this->m_LiftGimmickDifficultyType = EEndCrashBoxMiniGameLiftDifficultyType::ALL;
    this->m_bLiftPartsEnable = false;
    this->m_LiftPartsPositionZ = 0.00f;
}

void AEndCrashBoxMiniGameLiftRootActor::SetReferenceStaticMesh(EEndCrashBoxMiniGameLiftPartsType Type, UStaticMeshComponent* StaticMeshComp) {
}

void AEndCrashBoxMiniGameLiftRootActor::SetLiftActor(AEndEnvironmentSkeletalMeshActor* LiftActor) {
}

void AEndCrashBoxMiniGameLiftRootActor::SetLeverActor(AEndCrashBoxMiniGameLiftLeverActor* LeverActor) {
}

void AEndCrashBoxMiniGameLiftRootActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}

void AEndCrashBoxMiniGameLiftRootActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}

void AEndCrashBoxMiniGameLiftRootActor::LiftPartsInitialize() {
}


