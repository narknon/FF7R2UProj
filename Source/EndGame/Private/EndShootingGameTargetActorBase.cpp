#include "EndShootingGameTargetActorBase.h"
#include "Components/SceneComponent.h"

AEndShootingGameTargetActorBase::AEndShootingGameTargetActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}


