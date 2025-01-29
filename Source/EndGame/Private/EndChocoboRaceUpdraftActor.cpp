#include "EndChocoboRaceUpdraftActor.h"
#include "Components/SceneComponent.h"

AEndChocoboRaceUpdraftActor::AEndChocoboRaceUpdraftActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->TargetHeight = 800.00f;
}


