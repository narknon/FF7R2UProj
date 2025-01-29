#include "EndGambitSpawnEnemyInfo.h"

FEndGambitSpawnEnemyInfo::FEndGambitSpawnEnemyInfo() {
    this->GenerateRate = 0;
    this->WatchingType = EEndGambitSpawnWatchingType::Watch_None;
    this->WatchingRateParam = 0.00f;
    this->SpawnPointSelection = EEndGambitSpawnLaneSelectionType::Spawn_Here;
    this->bWatchingOrIntervalTime = false;
}

