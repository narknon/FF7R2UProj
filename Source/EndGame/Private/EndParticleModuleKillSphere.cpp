#include "EndParticleModuleKillSphere.h"

UEndParticleModuleKillSphere::UEndParticleModuleKillSphere() {
    this->bUpdateModule = true;
    this->bSupported3DDrawMode = true;
    this->m_RefPointName = TEXT("Point_1");
    this->m_EnableIfHitRayCastPoint = false;
    this->m_KillOutSize = false;
    this->m_ParticleLoopOff = false;
    this->m_SendTrigger = false;
    this->m_SendTriggerParticleCount = 0;
    this->m_EffectLoopOff = false;
}


