#include "EndNiagaraDataInterfaceForceFeedback.h"

UEndNiagaraDataInterfaceForceFeedback::UEndNiagaraDataInterfaceForceFeedback() {
    this->m_PriorityTrack = EEndForceFeedbackTrack::FFB_Track3;
    this->m_Effect = EEndForceFeedbackEffect::FFB_Effect0;
    this->m_bWithPriorityControl = true;
}


