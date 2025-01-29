#include "EndChocoboRaceConveyorActorBase.h"
#include "Components/SceneComponent.h"

AEndChocoboRaceConveyorActorBase::AEndChocoboRaceConveyorActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}


