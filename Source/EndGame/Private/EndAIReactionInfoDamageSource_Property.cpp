#include "EndAIReactionInfoDamageSource_Property.h"

FEndAIReactionInfoDamageSource_Property::FEndAIReactionInfoDamageSource_Property() {
    this->DamageSource_Property = EEndBattleDamageSourceProperty::PhysicsNear;
    this->PlayerType = EEndAIReactionPlayerType::All;
}

