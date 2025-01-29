#include "EndParticleModuleEventSpawnEffect.h"

UEndParticleModuleEventSpawnEffect::UEndParticleModuleEventSpawnEffect() {
    this->bUpdateModule = true;
    this->m_EventKind = EE_EK_End;
    this->m_RefPointName = TEXT("Point_1");
    this->m_bAttachment = false;
    this->m_AttachActorKind = EELK_Self;
}


