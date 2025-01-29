#include "EndChocoboRaceBoundCushionActor.h"
#include "Components/SceneComponent.h"

AEndChocoboRaceBoundCushionActor::AEndChocoboRaceBoundCushionActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}


