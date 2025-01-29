#include "EndAnimNotifyStateBattleDamagePartyChocobo.h"

UEndAnimNotifyStateBattleDamagePartyChocobo::UEndAnimNotifyStateBattleDamagePartyChocobo() {
    this->DamageSourceIDs.AddDefaulted(1);
    this->CreateCondition = EEndAnimNotifyStateBattleDamagePartyChocoboCondition::PlayerRidingOnly;
}


