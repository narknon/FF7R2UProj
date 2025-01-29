#include "EndAnimNotifyBattleDamage.h"

UEndAnimNotifyBattleDamage::UEndAnimNotifyBattleDamage() {
    this->DamageSourceIDs.AddDefaulted(1);
    this->CreatePositionBase = EEndBattleDamageSourcePositionBaseType::Owner;
    this->ReplaceTargetCharaType = EEndBattleDamageSourceReplaceTargetCharaType::None;
    this->OwnerFilterType = EEndAnimNotifyBattleDamageOwnerFilterType::eALL;
    this->Display = false;
    this->Condition = EEndAnimNotifyBattleDamageCondition::None;
}


