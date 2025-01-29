#include "EndEnvironmentAccessorGroupActor.h"
#include "Components/SceneComponent.h"

AEndEnvironmentAccessorGroupActor::AEndEnvironmentAccessorGroupActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bRelevantForLevelBounds = false;
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
}


