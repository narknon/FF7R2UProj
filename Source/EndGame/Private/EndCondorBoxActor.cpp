#include "EndCondorBoxActor.h"
#include "Components/SceneComponent.h"

AEndCondorBoxActor::AEndCondorBoxActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}


