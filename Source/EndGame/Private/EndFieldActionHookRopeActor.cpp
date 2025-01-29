#include "EndFieldActionHookRopeActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionHookRopeActor::AEndFieldActionHookRopeActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->UpperVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("UpperVolume"));
    this->RopeType = EHookRopeType::TarzanRope;
    this->SwingAngle = 70.00f;
    this->CatchRopeLength = 500.00f;
    this->bHasTopArrivalTransform = false;
    this->bAutoClimbingRopeLength = true;
    this->RopeLength = 1000.00f;
    this->bHasClimginDownEntryPoint = true;
    this->bAutoClimbingDownEntryPoint = true;
    this->ClimbingDownEnterPointOffsetDistance = 0.00f;
    this->bUseIconDistanceMax = false;
    this->IconDistanceMax = 2000.00f;
    this->bUseSwingToMoveObject = false;
    this->RopeObjectClass = NULL;
    this->ClimbingRopeObjectClass = NULL;
    this->bUseHookPointMovingVibration = true;
    this->bCachedClimbingDownPoint = false;
    this->bHasCachedClimbing = false;
    this->ClimbingVersion = 0;
    this->ImpossibleSearchUIName = TEXT("Default__EndFieldActionHookRopeActor_ImpossibleUI");
    this->RailCameraSplineProgressSpeedCmps = 1000.00f;
    this->bUseStoryFlagRailCamera = false;
    this->StoryFlagRailCameraMinBlendInStartTime = 3.00f;
    this->StoryFlagRailCameraTimeout = 3.00f;
    this->StoryFlagRailCameraBlendTime = 3.00f;
    this->StoryFlagRailCameraBlendOption = EAlphaBlendOption::ExpInOut;
    this->StoryFlagRailCameraBlendOutTime = 3.00f;
    this->StoryFlagRailCameraBlendOutOption = EAlphaBlendOption::ExpInOut;
    this->UpperVolume->SetupAttachment(RootComponent);
}


