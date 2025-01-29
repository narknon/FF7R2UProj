#include "AnimNotify_EndWeaponVisibility.h"

UAnimNotify_EndWeaponVisibility::UAnimNotify_EndWeaponVisibility() {
    this->Slot = EWeaponSlot::EWeaponSlot_1;
    this->bVisible = false;
    this->bReleaseCharaSpecHidden = false;
}


