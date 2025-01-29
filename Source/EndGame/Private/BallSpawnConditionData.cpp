#include "BallSpawnConditionData.h"

FBallSpawnConditionData::FBallSpawnConditionData() {
    this->SpawnCondition = EBallSpawnCondition::SpawnElapsedTime;
    this->BallConditionVariable = 0;
}

