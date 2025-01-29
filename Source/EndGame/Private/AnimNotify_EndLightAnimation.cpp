#include "AnimNotify_EndLightAnimation.h"

UAnimNotify_EndLightAnimation::UAnimNotify_EndLightAnimation() {
    this->Modifier = EEndAnimationModifierType::Overlay;
    this->Curve = EEndAnimationCurveType::OneLoop;
    this->CurveAsset = NULL;
    this->bCurveEvaluateInLogarithmicSpace = true;
    this->bLoop = false;
    this->Duration = 1.00f;
    this->RandomAdditiveDuration = 0.00f;
    this->RandomOffset = 0.00f;
    this->BlendInTime = 0.20f;
    this->BlendOutTime = 0.20f;
    this->StartOffset = 0.00f;
    this->EndOffset = 0.00f;
}


