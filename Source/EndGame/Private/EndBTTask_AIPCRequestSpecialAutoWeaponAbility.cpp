#include "EndBTTask_AIPCRequestSpecialAutoWeaponAbility.h"

UEndBTTask_AIPCRequestSpecialAutoWeaponAbility::UEndBTTask_AIPCRequestSpecialAutoWeaponAbility() {
    this->NodeName = TEXT("[End][AIPC]RequestSpecialAutoWeaponAbility");
    this->Type = EAutoWeaponAbilitySpecialCaseType::None;
    this->bRequestRider = false;
}


