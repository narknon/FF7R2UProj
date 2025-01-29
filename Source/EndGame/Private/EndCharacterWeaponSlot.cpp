#include "EndCharacterWeaponSlot.h"

FEndCharacterWeaponSlot::FEndCharacterWeaponSlot() {
    this->bDefaultVisibilityOnNeutral = false;
    this->bDefaultVisibilityOnBattle = false;
    this->bOverrideVisibility = false;
    this->OverrideVisibilityFrom = NULL;
    this->OverrideSocketNameFrom = NULL;
}

