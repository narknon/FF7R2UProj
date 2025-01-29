#include "EndNiagaraDataInterfaceAppendixMesh.h"

UEndNiagaraDataInterfaceAppendixMesh::UEndNiagaraDataInterfaceAppendixMesh() {
    this->m_EffectAppendixMesh = NULL;
    this->m_bReferencesGPUSkin = false;
    this->m_bReferencesGPUBone = false;
    this->m_bReferencesWheel = false;
    this->m_bReferencesFeelerTornade = false;
    this->m_BindAttachType = EEndAnimNotifyAttachType::None;
}


