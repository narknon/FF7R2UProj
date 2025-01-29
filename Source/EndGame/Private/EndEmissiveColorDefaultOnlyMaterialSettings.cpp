#include "EndEmissiveColorDefaultOnlyMaterialSettings.h"

FEndEmissiveColorDefaultOnlyMaterialSettings::FEndEmissiveColorDefaultOnlyMaterialSettings() {
    this->LayerIndex = 0;
    this->Curve = EEndAnimationCurveType::ZeroLoop;
    this->CurveAsset = NULL;
    this->bCurveEvaluateInLogarithmicSpace = false;
    this->Duration = 0.00f;
    this->RandomAdditiveDuration = 0.00f;
    this->RandomOffset = 0.00f;
}

