#include "EndFieldActionActorDoor.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndFieldMovementSettingVolumeComponent.h"
#include "EndNavModifierComponent.h"
#include "EndSwitchAreaBoxComponent.h"

AEndFieldActionActorDoor::AEndFieldActionActorDoor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bApplyUpdateOpenNavArea = false;
    this->DoorType = EDoorType::DoorKnobDoorVariation;
    this->bDisableDoorAnimation = false;
    this->DoorAdditionalThickness = 0.00f;
    this->bForceHeavyDoor = false;
    this->ForceHeavyDoorMotionRate = 0.40f;
    this->DisableForceAutoClose = false;
    this->DoorActiveEffectType = EDoorActiveEffectType::ActiveNone;
    this->bOpentDirIsReverse = false;
    this->bStateOpenIsReverse = false;
    this->bAddIconOffset = false;
    this->FindControllerKey = -1;
    this->DefaultDoorIconName = TEXT("rpaDoor");
    this->DefaultDoorIconPlayerName = TEXT("rpaDoorPlayer");
    this->bForceDisableCamera = false;
    this->bEnableTemporaryCameraCollision = true;
    this->PressVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PressVolume"));
    this->PullVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PullVolume"));
    this->DividedVersatileVolume = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("DividedVersatileVolume"));
    this->DividedImpassableVolume = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("DividedImpassableVolume"));
    this->OpendDoorVolumeLeft = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("OpendDoorVolumeLeft"));
    this->OpendDoorVolumeRight = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("OpendDoorVolumeRight"));
    this->OpendDoorVolumeLeft2 = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("OpendDoorVolumeLeft2"));
    this->OpendDoorVolumeRight2 = CreateDefaultSubobject<UEndSwitchAreaBoxComponent>(TEXT("OpendDoorVolumeRight2"));
    this->CanUseType = EDoorCanUseType::All;
    this->DoorOpenDegrees = 90.00f;
    this->DoorOpenMoveSpeed = 60.00f;
    this->DoorCloseMoveSpeed = 60.00f;
    this->bDoorSaveDataLoadOnlyExit = false;
    this->DoorSoundCallPosType = EDoorSoundCallPosType::DoorCenterGround;
    this->DoorSoundOverrideAttenuationSetting = NULL;
    this->bForceDisableNPCNoNaviWalk = false;
    this->bAdjustLoadOpenAfterOnOffLayout = false;
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->TikableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableVolume"));
    this->MovementSettingVolume = CreateDefaultSubobject<UEndFieldMovementSettingVolumeComponent>(TEXT("SettingVolume"));
    this->LongInputIconPressName = TEXT("Default__EndFieldActionActorDoor_PressLongIputIconName");
    this->LongInputIconPullName = TEXT("Default__EndFieldActionActorDoor_PullLongIputIconName");
    this->DividedImpassableVolume->SetupAttachment(RootComponent);
    this->DividedVersatileVolume->SetupAttachment(RootComponent);
    this->MovementSettingVolume->SetupAttachment(RootComponent);
    this->OpendDoorVolumeLeft->SetupAttachment(RootComponent);
    this->OpendDoorVolumeLeft2->SetupAttachment(RootComponent);
    this->OpendDoorVolumeRight->SetupAttachment(RootComponent);
    this->OpendDoorVolumeRight2->SetupAttachment(RootComponent);
    this->PressVolume->SetupAttachment(RootComponent);
    this->PullVolume->SetupAttachment(RootComponent);
    this->TikableVolume->SetupAttachment(RootComponent);
}


