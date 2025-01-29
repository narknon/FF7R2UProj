#include "EndAnimNotifyBattleDamageDisplay.h"

UDEPRECATED_EndAnimNotifyBattleDamageDisplay::UDEPRECATED_EndAnimNotifyBattleDamageDisplay() {
    this->DamageSourceID = TEXT("?");
    this->CreatePositionBase = EEndBattleDamageSourcePositionBaseType::Owner;
    this->OwnerFilterType = EEndAnimNotifyBattleDamageOwnerFilterType::eALL;
}


