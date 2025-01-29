#include "EndChickenLureMiniGameSkeletalCanActor.h"

AEndChickenLureMiniGameSkeletalCanActor::AEndChickenLureMiniGameSkeletalCanActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_SkeletalMeshComponent = NULL;
}

void AEndChickenLureMiniGameSkeletalCanActor::SetRopeLootActor(AEndEnvironmentSkeletalMeshActor* RopeLootActor) {
}

void AEndChickenLureMiniGameSkeletalCanActor::SetReferenceSkeletalMesh(USkeletalMeshComponent* SkeletalMeshComp) {
}

void AEndChickenLureMiniGameSkeletalCanActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}


