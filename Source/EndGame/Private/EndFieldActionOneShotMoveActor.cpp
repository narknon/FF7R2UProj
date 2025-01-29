#include "EndFieldActionOneShotMoveActor.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndFieldActionTriggerCustomComponent.h"
#include "EndNavWorldLinkAttrIgnoreBoxComponent.h"
#include "EndSwitchAreaBoxComponent.h"

AEndFieldActionOneShotMoveActor::AEndFieldActionOneShotMoveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->TikableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableVolume"));
    this->MoveType = EEndOneShotMoveType::Crack;
    this->RightEnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerCustomComponent>(TEXT("RightEnterVolume"));
    this->LeftEnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerCustomComponent>(TEXT("LeftEnterVolume"));
    this->OneShotDirType = EEndOneShotMoveDirType::BothWays;
    this->bHideEnterIcon = false;
    this->RightWorldLinkIgnoreVolume = CreateDefaultSubobject<UEndNavWorldLinkAttrIgnoreBoxComponent>(TEXT("RightWorldLinkIgnoreVolume"));
    this->LeftWorldLinkIgnoreVolume = CreateDefaultSubobject<UEndNavWorldLinkAttrIgnoreBoxComponent>(TEXT("LeftWorldLinkIgnoreVolume"));
    this->bUseImpassableVolume = false;
    this->NavImpassableVolume = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("DividedImpassableVolume"));
    this->LeftEnterVolume->SetupAttachment(RootComponent);
    this->LeftWorldLinkIgnoreVolume->SetupAttachment(RootComponent);
    this->NavImpassableVolume->SetupAttachment(RootComponent);
    this->RightEnterVolume->SetupAttachment(RootComponent);
    this->RightWorldLinkIgnoreVolume->SetupAttachment(RootComponent);
    this->TikableVolume->SetupAttachment(RootComponent);
}


