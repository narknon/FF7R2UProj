#include "EndFieldActionActorCaitSithVent.h"
#include "EndFieldActionSplineComponent.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionActorCaitSithVent::AEndFieldActionActorCaitSithVent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->SplineComponent = CreateDefaultSubobject<UEndFieldActionSplineComponent>(TEXT("SplineComponent"));
    this->UpVectorSplineComponent = CreateDefaultSubobject<UEndFieldActionSplineComponent>(TEXT("UpVectorSplineComponent"));
    this->EnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PressVolume"));
    this->ExitVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PullVolume"));
    this->ModifierVolume = NULL;
    this->bEnablePassing = false;
    this->bOverrideMoveSpeed = false;
    this->OverrideMoveSpeed = 300.00f;
    this->NavAttributeChange = false;
    this->WaitReservation = true;
    this->EnterSoundBase = NULL;
    this->LoopSoundBase = NULL;
    this->LeaveSoundBase = NULL;
    this->EnterVolume->SetupAttachment(RootComponent);
    this->ExitVolume->SetupAttachment(RootComponent);
    this->SplineComponent->SetupAttachment(RootComponent);
    this->UpVectorSplineComponent->SetupAttachment(SplineComponent);
}


