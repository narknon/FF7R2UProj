#include "EndAIBattleEnemyTargetSelectConditionElement.h"

FEndAIBattleEnemyTargetSelectConditionElement::FEndAIBattleEnemyTargetSelectConditionElement() {
    this->bEnable = false;
    this->Priority = 0;
    this->CharacterType = EEndAIEnemyTargetSelectCharacterType::UCPC;
    this->ConditionType = EEndAIEnemyTargetSelectConditionType::None;
    this->bMatchExclusion = false;
    this->Ratio = 0;
    this->ContinuousLimit = 0;
}

