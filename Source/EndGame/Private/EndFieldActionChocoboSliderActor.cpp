#include "EndFieldActionChocoboSliderActor.h"
#include "EndFieldActionSplineComponent.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionChocoboSliderActor::AEndFieldActionChocoboSliderActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->SplineComponent = CreateDefaultSubobject<UEndFieldActionSplineComponent>(TEXT("SplineComponent"));
    this->EnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("EnterVolume"));
    this->ExitVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("ExitVolume"));
    this->WaitReservation = true;
    this->StartJumpLength = 300.00f;
    this->StartJumpAngle = 60.00f;
    this->EndJumpLength = 300.00f;
    this->EndJumpAngle = 60.00f;
    this->StartActionAngleThreshold = 60.00f;
    this->StartActionForwardCheckDistance = 500.00f;
    this->EnterVolume->SetupAttachment(RootComponent);
    this->ExitVolume->SetupAttachment(RootComponent);
    this->SplineComponent->SetupAttachment(RootComponent);
}


