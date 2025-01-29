#include "EndChickenLureMiniGameRopeRootActor.h"

AEndChickenLureMiniGameRopeRootActor::AEndChickenLureMiniGameRopeRootActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanBeInCluster = false;
    this->RopeClass = NULL;
    this->SkeletalCanClass = NULL;
    this->m_RopeSkeletalMeshComponent = NULL;
    this->m_CanSkeletalMeshComponent = NULL;
}

void AEndChickenLureMiniGameRopeRootActor::SetSkeletalCanActor(AEndChickenLureMiniGameSkeletalCanActor* CanActor) {
}

void AEndChickenLureMiniGameRopeRootActor::SetRopeActor(AActor* RopeActor) {
}

void AEndChickenLureMiniGameRopeRootActor::SetReferenceSkeletalCanStaticMesh(USkeletalMeshComponent* SkeletalMeshComp) {
}


