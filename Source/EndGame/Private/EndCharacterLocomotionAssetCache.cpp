#include "EndCharacterLocomotionAssetCache.h"

FEndCharacterLocomotionAssetCache::FEndCharacterLocomotionAssetCache() {
    this->Asset = NULL;
    this->AnimGroup = EEndLocomotionAnimGroup::Idle;
    this->SubAnimGroup = EEndLocomotionAnimGroup::Idle;
    this->StartTime = 0.00f;
    this->CurrentTime = 0.00f;
    this->LastTime = 0.00f;
    this->BlendTime = 0.00f;
    this->bLooping = false;
    this->bOverrideLooping = false;
    this->bDirty = false;
}

