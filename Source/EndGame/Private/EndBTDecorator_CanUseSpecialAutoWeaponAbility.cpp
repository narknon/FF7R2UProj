#include "EndBTDecorator_CanUseSpecialAutoWeaponAbility.h"

UEndBTDecorator_CanUseSpecialAutoWeaponAbility::UEndBTDecorator_CanUseSpecialAutoWeaponAbility() {
    this->NodeName = TEXT("[End][AIPC]CanUseSpecialAutoWeaponAbility");
    this->Type = EAutoWeaponAbilitySpecialCaseType::None;
    this->bCheckRider = false;
}


