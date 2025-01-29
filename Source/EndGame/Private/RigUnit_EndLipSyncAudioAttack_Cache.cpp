#include "RigUnit_EndLipSyncAudioAttack_Cache.h"

FRigUnit_EndLipSyncAudioAttack_Cache::FRigUnit_EndLipSyncAudioAttack_Cache() {
    this->bNeedInitialize = false;
    this->CurrentEvaluateFrame = 0;
    this->LastEvaluateFrame = 0;
    this->CurrentAudioPower = 0.00f;
    this->LastAudioPower = 0.00f;
    this->AttackAnimationBlendRate = 0.00f;
    this->BrowAnimationBlendRate = 0.00f;
}

