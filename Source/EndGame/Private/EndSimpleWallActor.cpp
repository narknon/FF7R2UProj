#include "EndSimpleWallActor.h"
#include "Components/StaticMeshComponent.h"

AEndSimpleWallActor::AEndSimpleWallActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
}


