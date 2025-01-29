#include "VfxParticleModuleFadeByEmitterAngle.h"

UVfxParticleModuleFadeByEmitterAngle::UVfxParticleModuleFadeByEmitterAngle() {
    this->bSpawnModule = true;
    this->bUpdateModule = true;
    this->bSupported3DDrawMode = true;
    this->m_LimitAngle = 90.00f;
    this->m_BlendAngle = 20.00f;
    this->m_VisibleDistance = 0.00f;
    this->m_BlendDistance = 50.00f;
}


