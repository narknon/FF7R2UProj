#include "RigUnit_EndLookAround_Cache.h"

FRigUnit_EndLookAround_Cache::FRigUnit_EndLookAround_Cache() {
    this->State = EEndLookAroundState::None;
    this->CurrentEmotionalGesture = EEndEmotionalGesture::None;
    this->LastEmotionalGesture = EEndEmotionalGesture::None;
    this->bOnlySaccade = false;
    this->EmotionalGestureTimer = 0.00f;
    this->LookAroundWaitTimer = 0.00f;
    this->LookAroundWaitTimeMax = 0.00f;
    this->LargeLookAroundWaitTimer = 0.00f;
    this->LargeLookAroundWaitTimeMax = 0.00f;
    this->SmallLookAroundWaitTimer = 0.00f;
    this->SmallLookAroundWaitTimeMax = 0.00f;
    this->MicroLookAroundWaitTimer = 0.00f;
    this->MicroLookAroundWaitTimeMax = 0.00f;
    this->LookAtTargetYaw = 0.00f;
    this->LookAtTargetPitch = 0.00f;
    this->SaccadeOffsetYaw = 0.00f;
    this->SaccadeOffsetPitch = 0.00f;
}

