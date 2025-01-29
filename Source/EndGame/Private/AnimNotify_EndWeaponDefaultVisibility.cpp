#include "AnimNotify_EndWeaponDefaultVisibility.h"

UAnimNotify_EndWeaponDefaultVisibility::UAnimNotify_EndWeaponDefaultVisibility() {
    this->Slot = EWeaponSlot::EWeaponSlot_1;
    this->BehaviorMode = EEndAnimBehaviorMode::Neutral;
    this->bVisible = false;
    this->bReleaseCharaSpecHidden = false;
}


