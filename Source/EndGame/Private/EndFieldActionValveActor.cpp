#include "EndFieldActionValveActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionValveActor::AEndFieldActionValveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->TikableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableVolume"));
    this->HandleRotCount = 5;
    this->ValveSoundBank = NULL;
    this->TikableVolume->SetupAttachment(RootComponent);
}


