#include "EndDeformAnimationSettings.h"

FEndDeformAnimationSettings::FEndDeformAnimationSettings() {
    this->NumberOfContext = 0;
    this->NumberOfKey = 0;
    this->PlayRate = 0.00f;
    this->bPlayLoopAnimationOnSpawn = false;
    this->bUsePhysicsAssetBounds = false;
    this->OptionalBoundsScale = 0.00f;
}

