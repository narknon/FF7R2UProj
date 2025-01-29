#include "RigUnit_EndSaccade_Cache.h"

FRigUnit_EndSaccade_Cache::FRigUnit_EndSaccade_Cache() {
    this->bNeedInitialize = false;
    this->bLastActiveSaccade = false;
    this->BlendRate = 0.00f;
    this->SaccadeWaitTimer = 0.00f;
    this->MicroSaccadeWaitTimer = 0.00f;
    this->bActiveRandomOverrideSaccade = false;
    this->RandomOverrideSaccadeWaitTimer = 0.00f;
    this->BlinkTimer = 0.00f;
    this->BlinkRate = 0.00f;
    this->BlinkBias = 0.00f;
    this->BlinkCurve = NULL;
    this->NextBlinkTime = 0.00f;
    this->bRequestedRefrectiveBlink = false;
    this->ReflectiveBlinkWaitTimer = 0.00f;
}

