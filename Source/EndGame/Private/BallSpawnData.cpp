#include "BallSpawnData.h"

FBallSpawnData::FBallSpawnData() {
    this->ConditionType = EBallSpawnConditionType::Once;
    this->TeamType = ETeamType::TeamA;
    this->Number = 0;
}

