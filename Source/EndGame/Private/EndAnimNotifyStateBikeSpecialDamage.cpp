#include "EndAnimNotifyStateBikeSpecialDamage.h"

UEndAnimNotifyStateBikeSpecialDamage::UEndAnimNotifyStateBikeSpecialDamage() {
    this->DamageSourceID = TEXT("?");
    this->CreatePositionBase = EEndBikeDamageSourcePositionBaseType::Owner;
    this->Parameter = 0;
}


