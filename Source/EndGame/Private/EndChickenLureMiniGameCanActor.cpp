#include "EndChickenLureMiniGameCanActor.h"

AEndChickenLureMiniGameCanActor::AEndChickenLureMiniGameCanActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanBeInCluster = false;
    this->m_StaticMeshComponent = NULL;
}

void AEndChickenLureMiniGameCanActor::SetRopeLootActor(AEndEnvironmentSkeletalMeshActor* RopeLootActor) {
}

void AEndChickenLureMiniGameCanActor::SetReferenceStaticMesh(UStaticMeshComponent* StaticMeshComp) {
}

void AEndChickenLureMiniGameCanActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}


