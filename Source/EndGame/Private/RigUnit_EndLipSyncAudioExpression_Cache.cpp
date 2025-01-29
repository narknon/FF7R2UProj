#include "RigUnit_EndLipSyncAudioExpression_Cache.h"

FRigUnit_EndLipSyncAudioExpression_Cache::FRigUnit_EndLipSyncAudioExpression_Cache() {
    this->bNeedInitialize = false;
    this->bPlaying = false;
    this->CurrentEvaluateFrame = 0;
    this->LastEvaluateFrame = 0;
    this->CurrentAudioPower = 0.00f;
    this->LastAudioPower = 0.00f;
    this->CachedDeltaTime0 = 0.00f;
    this->CachedDeltaTime1 = 0.00f;
}

