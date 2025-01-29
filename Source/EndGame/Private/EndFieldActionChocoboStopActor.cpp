#include "EndFieldActionChocoboStopActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionChocoboStopActor::AEndFieldActionChocoboStopActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->UpperVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("UpperVolume"));
    this->bDeactiveIsDown = false;
    this->IconInputSuccessTime = 6.00f;
    this->ChocoboIconInputSuccessTime = 2.00f;
    this->FeatherActorClass = NULL;
    this->UpperVolume->SetupAttachment(RootComponent);
}


