#include "VfxParticleModuleEventTrigger.h"

UVfxParticleModuleEventTrigger::UVfxParticleModuleEventTrigger() {
    this->bUpdateModule = true;
    this->bRequiresLoopingNotification = true;
    this->m_TriggerType = EVfxParticleEventTriggerType::EVPETT_None;
    this->m_TriggerTime = 0.00f;
    this->m_TriggerParam = 0;
    this->m_bRepeatTrigger = false;
}


