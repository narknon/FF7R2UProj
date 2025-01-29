#include "EndFieldActionRedHoldCrushActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionRedHoldCrushActor::AEndFieldActionRedHoldCrushActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->RedHoldCrushVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("RedHoldCrushVolume"));
    this->LongTimerMax = 2.00f;
    this->RedHoldCrushVolume->SetupAttachment(RootComponent);
}


