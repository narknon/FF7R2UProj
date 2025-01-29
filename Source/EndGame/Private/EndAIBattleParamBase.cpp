#include "EndAIBattleParamBase.h"

UEndAIBattleParamBase::UEndAIBattleParamBase() {
    this->CombatDistance = 400.00f;
    this->CautionDistance = 800.00f;
    this->bUseAerialParam = false;
    this->CautionTimeMax = 0.00f;
    this->CautionTimeMin = 0.00f;
    this->AerialCautionTimeMax = 0.00f;
    this->AerialCautionTimeMin = 0.00f;
}


