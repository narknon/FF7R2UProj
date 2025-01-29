#include "EndPathWayBoxActor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "EndNavModifierComponent.h"

AEndPathWayBoxActor::AEndPathWayBoxActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->PathWayBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("PathWayBoxComponent"));
    this->PathWayModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("PathWayModifier"));
    this->PathWayBoxComponent->SetupAttachment(RootComponent);
}


