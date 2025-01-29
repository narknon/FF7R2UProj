#include "EndMobPrefabRegistry.h"

FEndMobPrefabRegistry::FEndMobPrefabRegistry() {
    this->bNoGroundDefault = false;
    this->bNoGroundInstance = false;
    this->FitGroundType = EEndMobPrefabFitGroundType::FitGroundAndIK;
    this->InitialLookAtBlendRate = 0.00f;
    this->InitialLoopMotion = NULL;
    this->AnimSet = NULL;
}

