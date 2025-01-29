#include "AnimNotify_EndLightAnimationRange.h"

UAnimNotify_EndLightAnimationRange::UAnimNotify_EndLightAnimationRange() {
    this->Modifier = EEndAnimationModifierType::Overlay;
    this->Curve = EEndAnimationCurveType::OneLoop;
    this->CurveAsset = NULL;
    this->bCurveEvaluateInLogarithmicSpace = true;
    this->Duration = 1.00f;
    this->RandomAdditiveDuration = 0.00f;
    this->RandomOffset = 0.00f;
    this->BlendInTime = 0.20f;
    this->BlendOutTime = 0.20f;
    this->bCallStopOnEnd = true;
}


