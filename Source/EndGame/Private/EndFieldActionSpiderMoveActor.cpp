#include "EndFieldActionSpiderMoveActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionSpiderMoveActor::AEndFieldActionSpiderMoveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->TickableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TickableVolume"));
    this->FrontWallDistance = 44.00f;
    this->TickableVolume->SetupAttachment(RootComponent);
}


