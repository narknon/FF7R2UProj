#include "EndFieldActionActorHookShotChild.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndHoocShotTriggerComponent.h"
#include "EndNavModifierComponent.h"

AEndFieldActionActorHookShotChild::AEndFieldActionActorHookShotChild(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->PressVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PressVolume"));
    this->TargetVolume = CreateDefaultSubobject<UEndHoocShotTriggerComponent>(TEXT("TargetVolume"));
    this->ArrivalVolume = CreateDefaultSubobject<UEndHoocShotTriggerComponent>(TEXT("ArrivalVolume"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->IconEnableAngle = 80.00f;
    this->NgIconStartRadius = 4000.00f;
    this->IconOffStartRadius = -1.00f;
    this->GunObjectClass = NULL;
    this->NpcStartPointNum = 1;
    this->SoundBank_HookShotHit = NULL;
    this->ArrivalVolume->SetupAttachment(RootComponent);
    this->PressVolume->SetupAttachment(RootComponent);
    this->TargetVolume->SetupAttachment(RootComponent);
}


