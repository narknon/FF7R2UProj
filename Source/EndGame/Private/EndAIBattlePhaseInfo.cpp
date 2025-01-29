#include "EndAIBattlePhaseInfo.h"

FEndAIBattlePhaseInfo::FEndAIBattlePhaseInfo() {
    this->HPPercent = 0;
    this->HpPercent_Heard = 0;
    this->HpPercent_Easy = 0;
    this->ActionIdType = EEndAIBattlePhaseChangeActionIdType::ReactionId;
    this->bUseManualPhaseChange = false;
    this->bManualPhaseChangeAndHpLimit = false;
    this->bEnableHpLimitUIAlways = false;
}

