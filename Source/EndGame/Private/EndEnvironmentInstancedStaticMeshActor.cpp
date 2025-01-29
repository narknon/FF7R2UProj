#include "EndEnvironmentInstancedStaticMeshActor.h"
#include "Components/InstancedStaticMeshComponent.h"

AEndEnvironmentInstancedStaticMeshActor::AEndEnvironmentInstancedStaticMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanBeInCluster = true;
    this->RootComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMesh"));
    this->InstancedMeshComponent = (UInstancedStaticMeshComponent*)RootComponent;
    this->bUseAnimation = false;
    this->AnimateTime = 0.00f;
    this->AnimateTimeRate = 1.00f;
    this->AnimateTimeMax = 1000000.00f;
}


