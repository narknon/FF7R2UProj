#include "VFXNiagaraCreateParams.h"

FVFXNiagaraCreateParams::FVFXNiagaraCreateParams() {
    this->m_bEnable = false;
    this->m_Attached = false;
    this->m_bSynchroParentActorTick = false;
    this->m_NotifyRotationKind = EVFXAttachRotationKind::EVNR_Socket;
}

