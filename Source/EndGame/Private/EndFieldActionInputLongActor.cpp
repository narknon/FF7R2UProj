#include "EndFieldActionInputLongActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionInputLongActor::AEndFieldActionInputLongActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->TikableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableVolume"));
    this->LongInputTimeMax = 1.50f;
    this->bIconTransIsAttachPoint = false;
    this->TikableVolume->SetupAttachment(RootComponent);
}


