#include "EndFieldActionActorAutoDoor.h"
#include "EndFieldActionTriggerCustomComponent.h"
#include "EndNavModifierComponent.h"
#include "EndSwitchAreaBoxComponent.h"

AEndFieldActionActorAutoDoor::AEndFieldActionActorAutoDoor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->AutoDoorActiveEffectType = EAutoDoorActiveEffectType::AutoDoorActiveNone;
    this->OpenVolume = CreateDefaultSubobject<UEndFieldActionTriggerCustomComponent>(TEXT("OpenVolume"));
    this->CloseVolume = CreateDefaultSubobject<UEndFieldActionTriggerCustomComponent>(TEXT("CloseVolume"));
    this->TickVolume = CreateDefaultSubobject<UEndFieldActionTriggerCustomComponent>(TEXT("TickVolume"));
    this->DividedVersatileVolume = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("DividedVersatileVolume"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->AutoClosingTime = 3.00f;
    this->BattleInWayType = EEndOneWayType::RightToLeft;
    this->bDisableBattleIn = false;
    this->bCanOpenCutSceneBindChara = false;
    this->bIgnoreCheck_DisableFieldAction = false;
    this->bDeactiveIsEnableCollision = false;
    this->bBattleIsAlwaysClose = false;
    this->CloseVolume->SetupAttachment(RootComponent);
    this->DividedVersatileVolume->SetupAttachment(RootComponent);
    this->OpenVolume->SetupAttachment(RootComponent);
    this->TickVolume->SetupAttachment(RootComponent);
}


