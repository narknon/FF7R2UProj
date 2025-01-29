#include "EndEnvironmentAccessorActor.h"
#include "Components/SceneComponent.h"

AEndEnvironmentAccessorActor::AEndEnvironmentAccessorActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bRelevantForLevelBounds = false;
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
}


