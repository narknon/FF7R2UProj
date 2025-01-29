#include "EndCactusMissionConditionData.h"

FEndCactusMissionConditionData::FEndCactusMissionConditionData() {
    this->Condition = EEndAppearCondition::None;
    this->ConditionNum = 0;
    this->SubCondition = EEndAppearCondition::None;
    this->SubConditionNum = 0;
    this->ConditionPriority = 0;
}

