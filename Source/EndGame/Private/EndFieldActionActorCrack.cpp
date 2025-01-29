#include "EndFieldActionActorCrack.h"
#include "EndFieldActionSplineComponent.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndNavModifierComponent.h"
#include "EndNavWorldLinkAttrIgnoreBoxComponent.h"
#include "EndSwitchAreaBoxComponent.h"

AEndFieldActionActorCrack::AEndFieldActionActorCrack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->CrackComponent = CreateDefaultSubobject<UEndFieldActionSplineComponent>(TEXT("CrackComponent"));
    this->EnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PressVolume"));
    this->ExitVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PullVolume"));
    this->DividedImpassableEnterVolume = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("DividedImpassableEnterVolume"));
    this->DividedImpassableExitVolume = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("DividedImpassableExitVolume"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->bWalkPathMove = false;
    this->CrackMoveType = EEndCrackMoveType::FrontWall;
    this->GoalDistanceOffsetLeft = 0.00f;
    this->GoalDistanceOffsetRight = 0.00f;
    this->PointLinkOffsetLeft = 0.00f;
    this->PointLinkOffsetRight = 0.00f;
    this->ExceptionFlg = false;
    this->WaitReservation = true;
    this->NPCStartActionWaitBetweenCharaDistance = 140.00f;
    this->bUseForceFinishPointLeft = false;
    this->bUseForceFinishPointRight = false;
    this->RightWorldLinkIgnoreVolume = CreateDefaultSubobject<UEndNavWorldLinkAttrIgnoreBoxComponent>(TEXT("RightWorldLinkIgnoreVolume"));
    this->LeftWorldLinkIgnoreVolume = CreateDefaultSubobject<UEndNavWorldLinkAttrIgnoreBoxComponent>(TEXT("LeftWorldLinkIgnoreVolume"));
    this->CrackComponent->SetupAttachment(RootComponent);
    this->DividedImpassableEnterVolume->SetupAttachment(EnterVolume);
    this->DividedImpassableExitVolume->SetupAttachment(ExitVolume);
    this->EnterVolume->SetupAttachment(RootComponent);
    this->ExitVolume->SetupAttachment(RootComponent);
    this->LeftWorldLinkIgnoreVolume->SetupAttachment(RootComponent);
    this->RightWorldLinkIgnoreVolume->SetupAttachment(RootComponent);
}


