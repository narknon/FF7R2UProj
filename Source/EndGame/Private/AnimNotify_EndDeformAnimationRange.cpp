#include "AnimNotify_EndDeformAnimationRange.h"

UAnimNotify_EndDeformAnimationRange::UAnimNotify_EndDeformAnimationRange() {
    this->AnimationType = EEndDeformAnimationType::PlayOneShot;
    this->StartFrame = 0.00f;
    this->bCallStopOnEnd = true;
}


