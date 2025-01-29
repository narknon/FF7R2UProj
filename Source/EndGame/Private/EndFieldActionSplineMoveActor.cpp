#include "EndFieldActionSplineMoveActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionSplineMoveActor::AEndFieldActionSplineMoveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->TikableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableVolume"));
    this->MoveType = EEndFieldSplineMoveType::Balance;
    this->bUpdateNaviLink = false;
    this->TikableVolume->SetupAttachment(RootComponent);
}


