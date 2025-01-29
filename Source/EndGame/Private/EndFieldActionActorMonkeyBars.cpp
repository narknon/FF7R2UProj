#include "EndFieldActionActorMonkeyBars.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionActorMonkeyBars::AEndFieldActionActorMonkeyBars(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->TickableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TickableVolume"));
    this->BarStaticMeshActor = NULL;
    this->BarSkeletalMeshActor = NULL;
    this->TickableVolume->SetupAttachment(RootComponent);
}


