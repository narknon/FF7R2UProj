#include "EndParticleModuleFitGround.h"

UEndParticleModuleFitGround::UEndParticleModuleFitGround() {
    this->bUpdateModule = true;
    this->bSupported3DDrawMode = true;
    this->m_RayCastUp = 100.00f;
    this->m_RayCastDown = 400.00f;
    this->m_Timer = 0.00f;
    this->m_GroundOffset = 0.10f;
    this->m_FitNormal = false;
}


