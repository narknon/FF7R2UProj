#include "EndParticleModuleLight.h"

UEndParticleModuleLight::UEndParticleModuleLight() {
    this->bUpdateModule = true;
    this->bSupported3DDrawMode = true;
    this->m_LightKind = EVfxEffectLightKind::Unpunctual;
    this->m_SourceLengthOffsetRate = 0.00f;
    this->m_bIsBeamLight = false;
    this->m_bRenderVolumetricFogOnly = false;
}


