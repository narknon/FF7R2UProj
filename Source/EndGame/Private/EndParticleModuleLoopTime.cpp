#include "EndParticleModuleLoopTime.h"

UEndParticleModuleLoopTime::UEndParticleModuleLoopTime() {
    this->bSpawnModule = true;
    this->m_fBeginLoop = 0.50f;
    this->m_fEndLoop = 0.50f;
    this->m_PerParticleLoop = false;
}


