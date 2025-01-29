#include "EndLightAnimationActor.h"
#include "Components/SceneComponent.h"

AEndLightAnimationActor::AEndLightAnimationActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}


