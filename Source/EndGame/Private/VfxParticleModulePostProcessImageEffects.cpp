#include "VfxParticleModulePostProcessImageEffects.h"

UVfxParticleModulePostProcessImageEffects::UVfxParticleModulePostProcessImageEffects() {
    this->bUpdateModule = true;
    this->bSupported3DDrawMode = true;
    this->bOverride_VignetteIntensity = false;
    this->bOverride_GrainIntensity = false;
    this->bOverride_GrainPosition = false;
    this->bOverride_ChromaticAberrationIntensity = false;
    this->bOverride_ChromaticSaturation = false;
    this->bOverride_NormalizedTintIntensity = false;
    this->bOverride_NormalizedTintColor = false;
    this->bOverride_NormalizedTintGradient = false;
    this->bOverride_NormalizedTintField = false;
    this->bOverride_NormalizedTintGain = false;
    this->bOverride_ContrastIntensity = false;
    this->bOverride_CompositeSDRIntensity = false;
}


