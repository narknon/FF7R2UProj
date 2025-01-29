#include "EndCharacterAbilityCancelParameter.h"

FEndCharacterAbilityCancelParameter::FEndCharacterAbilityCancelParameter() {
    this->Number = 0;
    this->Timing = 0;
    this->ComboCondition = EndBattleAbilityCancelComboCondition::None;
    this->Combo = 0;
}

