#include "EndPhysicsSEComponent.h"

UEndPhysicsSEComponent::UEndPhysicsSEComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->MeshComponent = NULL;
}

void UEndPhysicsSEComponent::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}


