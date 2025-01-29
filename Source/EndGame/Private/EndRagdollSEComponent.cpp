#include "EndRagdollSEComponent.h"

UEndRagdollSEComponent::UEndRagdollSEComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->CachedMeshComponent = NULL;
}

void UEndRagdollSEComponent::OnHitRagdoll(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}


