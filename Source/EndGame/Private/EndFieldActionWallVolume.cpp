#include "EndFieldActionWallVolume.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

AEndFieldActionWallVolume::AEndFieldActionWallVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    this->BoxComponent->SetupAttachment(RootComponent);
}


