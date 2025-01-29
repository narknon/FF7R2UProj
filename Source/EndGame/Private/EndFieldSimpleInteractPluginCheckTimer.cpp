#include "EndFieldSimpleInteractPluginCheckTimer.h"

UEndFieldSimpleInteractPluginCheckTimer::UEndFieldSimpleInteractPluginCheckTimer() {
    this->ElapsedTime = -1.00f;
    this->CurrentAnimationPlayedTime = -1.00f;
    this->CurrentAnimationElapsedTime = -1.00f;
    this->CurrentAnimationRemainingTime = -1.00f;
    this->bDisalbePlayedAnimationNameMatching = false;
}


