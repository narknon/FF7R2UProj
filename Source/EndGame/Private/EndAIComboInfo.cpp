#include "EndAIComboInfo.h"

FEndAIComboInfo::FEndAIComboInfo() {
    this->ComboNumber = 0;
    this->bLastCombo = false;
    this->bSafeSelect = false;
    this->ActionDefinitionClass = NULL;
    this->ComboHitCondition = EEndAIComboHitCondition::Unconditionally;
    this->LotProbability = 0.00f;
}

