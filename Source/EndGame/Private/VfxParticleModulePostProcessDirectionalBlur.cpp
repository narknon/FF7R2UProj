#include "VfxParticleModulePostProcessDirectionalBlur.h"

UVfxParticleModulePostProcessDirectionalBlur::UVfxParticleModulePostProcessDirectionalBlur() {
    this->bUpdateModule = true;
    this->bSupported3DDrawMode = true;
    this->bOverride_DirectionalBlurDistortionIntensity = false;
    this->bOverride_DirectionalBlurDistortionGradient = false;
    this->bOverride_DirectionalBlurDistortionField = false;
    this->bOverride_DirectionalBlurDistortionFrequency = false;
    this->bOverride_DirectionalBlurDistortionPosition = false;
}


