#include "EndFieldActionClimbingActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionClimbingActor::AEndFieldActionClimbingActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->UpperVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("UpperVolume"));
    this->RegulationClearVersion = -1;
    this->bFallStartIsForceCatch = false;
    this->RailCameraSplineComponent = NULL;
    this->bAutoUpdateRailCameraSplineComponent = false;
    this->bSetRailCameraSplineComponentToLinear = false;
    this->RailCameraProgressSpeed = 1.00f;
    this->UpperVolume->SetupAttachment(RootComponent);
}


