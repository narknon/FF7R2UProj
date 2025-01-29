#include "EndChocoboRaceDashFloorActor.h"
#include "Components/SceneComponent.h"

AEndChocoboRaceDashFloorActor::AEndChocoboRaceDashFloorActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}


