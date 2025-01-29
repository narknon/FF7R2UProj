#include "EndFieldActionBarretComboActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionBarretComboActor::AEndFieldActionBarretComboActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->TikableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableVolume"));
    this->HotFixComboNum = 30;
    this->TikableVolume->SetupAttachment(RootComponent);
}


