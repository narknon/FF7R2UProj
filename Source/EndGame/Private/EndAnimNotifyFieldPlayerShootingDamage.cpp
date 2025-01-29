#include "EndAnimNotifyFieldPlayerShootingDamage.h"

UEndAnimNotifyFieldPlayerShootingDamage::UEndAnimNotifyFieldPlayerShootingDamage() {
    this->DamageSourceID = TEXT("?");
    this->CreatePositionBase = EEndBattleDamageSourcePositionBaseType::Owner;
    this->Display = false;
}


