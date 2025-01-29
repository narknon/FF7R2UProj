#include "EndFieldActionWallRunningActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionWallRunningActor::AEndFieldActionWallRunningActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->WallRunningVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("WallRunningVolume"));
    this->bWallRunningVolume_BlockBoxOutMove = false;
    this->bWallRunningVolume_SetJumpDownPoint = false;
    this->bDebugViewBoxs = true;
    this->RailCameraSplineComponent = NULL;
    this->WallRunningVolume->SetupAttachment(RootComponent);
}


