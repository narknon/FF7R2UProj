#include "EndFieldActionActorLadder.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndNavModifierComponent.h"
#include "EndNavWorldLinkAttrIgnoreBoxComponent.h"

AEndFieldActionActorLadder::AEndFieldActionActorLadder(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->RungCount = 20;
    this->UpperSpace = 60.00f;
    this->LowerSpace = 60.00f;
    this->AdditionalLinkSpace = 35.00f;
    this->IsBrokenLadder = false;
    this->ExceptionFlg = false;
    this->WaitReservation = true;
    this->TickVolume = NULL;
    this->UpperVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("UpperVolume"));
    this->LowerVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("LowerVolume"));
    this->RightWorldLinkIgnoreVolume = CreateDefaultSubobject<UEndNavWorldLinkAttrIgnoreBoxComponent>(TEXT("RightWorldLinkIgnoreVolume"));
    this->LeftWorldLinkIgnoreVolume = CreateDefaultSubobject<UEndNavWorldLinkAttrIgnoreBoxComponent>(TEXT("LeftWorldLinkIgnoreVolume"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->LinkType = ENavLinkDirection::BothWays;
    this->LeftWorldLinkIgnoreVolume->SetupAttachment(RootComponent);
    this->LowerVolume->SetupAttachment(RootComponent);
    this->RightWorldLinkIgnoreVolume->SetupAttachment(RootComponent);
    this->UpperVolume->SetupAttachment(RootComponent);
}


