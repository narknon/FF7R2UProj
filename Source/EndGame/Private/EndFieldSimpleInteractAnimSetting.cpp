#include "EndFieldSimpleInteractAnimSetting.h"

FEndFieldSimpleInteractAnimSetting::FEndFieldSimpleInteractAnimSetting() {
    this->bDisalbePlayAnimationNameMatching = false;
    this->StartAnimationTime = 0.00f;
    this->StartAnimationTimeRate = 0.00f;
    this->bLoop = false;
    this->BlendInTime = 0.00f;
    this->FinishRemainingTime = 0.00f;
    this->FinishElapsedTime = 0.00f;
}

