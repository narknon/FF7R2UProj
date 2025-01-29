#include "EndMobPrefabRegistryOverride.h"

FEndMobPrefabRegistryOverride::FEndMobPrefabRegistryOverride() {
    this->bOverrideFitGroundType = false;
    this->FitGroundType = EEndMobPrefabFitGroundType::FitGroundAndIK;
}

