#include "EndFieldActionActorPipeSlide.h"
#include "EndFieldActionSplineComponent.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionActorPipeSlide::AEndFieldActionActorPipeSlide(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->SplineComponent = CreateDefaultSubobject<UEndFieldActionSplineComponent>(TEXT("SplineComponent"));
    this->EnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PressVolume"));
    this->ModifierVolume = NULL;
    this->bEnablePassing = false;
    this->bAutoRotateTriggers = true;
    this->bAutoReverseSplineToStartOnTop = true;
    this->NavAttributeChange = false;
    this->WaitReservation = true;
    this->bEnablePartyWarp = false;
    this->EnterVolume->SetupAttachment(RootComponent);
    this->SplineComponent->SetupAttachment(RootComponent);
}


