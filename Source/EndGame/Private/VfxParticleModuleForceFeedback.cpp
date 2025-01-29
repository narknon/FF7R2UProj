#include "VfxParticleModuleForceFeedback.h"

UVfxParticleModuleForceFeedback::UVfxParticleModuleForceFeedback() {
    this->bSupported3DDrawMode = true;
    this->m_PriorityTrack = EEndForceFeedbackTrack::FFB_Track3;
    this->m_Effect = EEndForceFeedbackEffect::FFB_Noise1;
    this->m_bWithPriorityControl = true;
}


