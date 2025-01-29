#include "EndNiagaraDataInterfaceTrail.h"

UEndNiagaraDataInterfaceTrail::UEndNiagaraDataInterfaceTrail() {
    this->m_MaxTrailCount = 0;
    this->m_PerTrailParticleCount = 0;
    this->m_RingBufferSize = 32;
    this->m_UpdateBufferFPS = 30;
}


