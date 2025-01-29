#include "EndGambitNestCharacter.h"

AEndGambitNestCharacter::AEndGambitNestCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->NestRecoverSec = 30.00f;
    this->NestRecoverRandomAddSec = 0.00f;
    this->SpawnEnemyFirstSec = 3.00f;
    this->SpawnIntervalSec = 10.00f;
    this->SpawnIntervalRandomAddSec = 0.00f;
    this->m_SpawnYawOffsetMain = 0.00f;
    this->m_SpawnSubOffsetRate = 0.00f;
    this->m_SpawnYawOffsetSub = 0.00f;
    this->bSpawnRandom = false;
    this->bSpawnOneOrder = true;
    this->bEnableStart = true;
    this->bGenerateOnce = true;
    this->bOnlySpawner = false;
}


