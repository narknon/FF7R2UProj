#include "EndFieldActionActorZipline.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionActorZipline::AEndFieldActionActorZipline(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->StartVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("StartVolume"));
    this->bUseEnterEffect = false;
    this->StartVolume->SetupAttachment(RootComponent);
}


