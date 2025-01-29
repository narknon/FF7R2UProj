#include "EndStaticMeshActorBase.h"
#include "EndStaticMeshComponent.h"

AEndStaticMeshActorBase::AEndStaticMeshActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndStaticMeshComponent>(TEXT("StaticMeshComponent0"))) {
    this->bCanBeInCluster = false;
    const FProperty* p_StaticMeshComponent = GetClass()->FindPropertyByName("StaticMeshComponent");
    (*p_StaticMeshComponent->ContainerPtrToValuePtr<UStaticMeshComponent*>(this)) = (UStaticMeshComponent*)RootComponent;
    this->DeformAnimationComponent = NULL;
    this->FlowMapAnimationComponent = NULL;
}


