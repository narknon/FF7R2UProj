#include "EndEnvProxyActor.h"
#include "EndEnvProxyStaticMeshComponent.h"

AEndEnvProxyActor::AEndEnvProxyActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndEnvProxyStaticMeshComponent>(TEXT("StaticMeshComponent0"));
    this->StaticMeshComponent = (UStaticMeshComponent*)RootComponent;
}


