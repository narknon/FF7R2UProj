#include "OverrideBattleParam.h"

FOverrideBattleParam::FOverrideBattleParam() {
    this->CombatDistance = 0.00f;
    this->CautionDistance = 0.00f;
    this->bUseParamFile = false;
    this->OverrideType = EAIPCBattleParamType::Normal;
}

