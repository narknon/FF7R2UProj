#include "EndAnimNotifyStateBattleDamage.h"

UEndAnimNotifyStateBattleDamage::UEndAnimNotifyStateBattleDamage() {
    this->DamageSourceIDs.AddDefaulted(1);
    this->Probability = 100;
    this->CreatePositionBase = EEndBattleDamageSourcePositionBaseType::Owner;
    this->ReplaceTargetCharaType = EEndBattleDamageSourceReplaceTargetCharaType::None;
    this->OwnerFilterType = EEndAnimNotifyBattleDamageOwnerFilterType::eALL;
    this->Condition = EEndAnimNotifyBattleDamageCondition::None;
}


