#include "EndEmissiveColorMaterial.h"

FEndEmissiveColorMaterial::FEndEmissiveColorMaterial() {
    this->LayerIndex = 0;
    this->bIntensityBlendInLogarithmicSpace = false;
    this->DefaultCurve = EEndAnimationCurveType::ZeroLoop;
    this->DefaultCurveAsset = NULL;
    this->bDefaultCurveEvaluateInLogarithmicSpace = false;
    this->DefaultDuration = 0.00f;
    this->DefaultRandomAdditiveDuration = 0.00f;
    this->DefaultRandomOffset = 0.00f;
    this->bUseGenericVector = false;
}

