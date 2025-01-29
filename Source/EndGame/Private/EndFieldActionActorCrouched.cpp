#include "EndFieldActionActorCrouched.h"
#include "EndFieldActionSplineComponent.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndNavModifierComponent.h"
#include "EndNavWorldLinkAttrIgnoreBoxComponent.h"
#include "EndSwitchAreaBoxComponent.h"

AEndFieldActionActorCrouched::AEndFieldActionActorCrouched(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->CrouchedType = ECrouchedType::FixCoordinates;
    this->CrouchedComponent = CreateDefaultSubobject<UEndFieldActionSplineComponent>(TEXT("CrouchedComponent"));
    this->EnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PressVolume"));
    this->ExitVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PullVolume"));
    this->DividedImpassableEnterVolume = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("DividedImpassableEnterVolume"));
    this->DividedImpassableExitVolume = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("DividedImpassableExitVolume"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->bWalkPathMove = false;
    this->bEnablePassing = false;
    this->CrouchedMoveType = EEndCrouchedMoveType::Default;
    this->GoalDistanceOffsetLeft = 0.00f;
    this->GoalDistanceOffsetRight = 0.00f;
    this->AutoBoxRotation = true;
    this->NavAttributeChange = false;
    this->WaitReservation = true;
    this->NPCStartActionWaitBetweenCharaDistance = 140.00f;
    this->bWideOverSpaceWakeActionArea = false;
    this->RightWorldLinkIgnoreVolume = CreateDefaultSubobject<UEndNavWorldLinkAttrIgnoreBoxComponent>(TEXT("RightWorldLinkIgnoreVolume"));
    this->LeftWorldLinkIgnoreVolume = CreateDefaultSubobject<UEndNavWorldLinkAttrIgnoreBoxComponent>(TEXT("LeftWorldLinkIgnoreVolume"));
    this->CrouchedComponent->SetupAttachment(RootComponent);
    this->DividedImpassableEnterVolume->SetupAttachment(EnterVolume);
    this->DividedImpassableExitVolume->SetupAttachment(ExitVolume);
    this->EnterVolume->SetupAttachment(RootComponent);
    this->ExitVolume->SetupAttachment(RootComponent);
    this->LeftWorldLinkIgnoreVolume->SetupAttachment(RootComponent);
    this->RightWorldLinkIgnoreVolume->SetupAttachment(RootComponent);
}


