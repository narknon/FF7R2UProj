#include "EndEmissiveColorPreviewSettings.h"

FEndEmissiveColorPreviewSettings::FEndEmissiveColorPreviewSettings() {
    this->ModifierType = EEndAnimationModifierType::Overlay;
    this->CurveType = EEndAnimationCurveType::ZeroLoop;
    this->CurveAsset = NULL;
    this->bCurveEvaluateInLogarithmicSpace = false;
    this->bLoop = false;
    this->Duration = 0.00f;
    this->RandomAdditiveDuration = 0.00f;
    this->RandomOffset = 0.00f;
    this->BlendInTime = 0.00f;
    this->BlendOutTime = 0.00f;
}

