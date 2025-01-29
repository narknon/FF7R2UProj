#include "EndPhysicsSeSetting.h"

FEndPhysicsSeSetting::FEndPhysicsSeSetting() {
    this->bEnable = false;
    this->HitImpulseThreshold = 0.00f;
    this->HitDistanceThreshold = 0.00f;
    this->HitImpulseSizeMax = 0.00f;
    this->HitAttenuationSetting = NULL;
    this->HitConcurrencySetting = NULL;
    this->FractureImpulseSizeMax = 0.00f;
    this->FractureAttenuationSetting = NULL;
    this->bWantsFragmentHit = false;
    this->bHitSensitive = false;
    this->HitSensitiveScalingValue = 0.00f;
    this->HitSoundAsset = NULL;
    this->FractureSoundAsset = NULL;
}

