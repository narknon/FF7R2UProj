#include "EndAIBattleGroupSetting.h"

FEndAIBattleGroupSetting::FEndAIBattleGroupSetting() {
    this->LeaderType = EEndAIBattleGroupLeader::None;
    this->bUseMoveDefinitionHerd = false;
    this->MoveDefinitionHerdClass = NULL;
}

