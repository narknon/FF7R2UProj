#include "SQEX_KineDriver_Component.h"

USQEX_KineDriver_Component::USQEX_KineDriver_Component(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->KineDriverIndex = -1;
    this->EnableScaleOpChildSSC = true;
    this->TickGroup = TG_AiControl;
    this->Enabled = true;
    this->EnableLOD = false;
    this->MinScreenSize = 0.01f;
    this->EnableFrustumCulling = false;
    this->EnableCheckDrawn = false;
}

void USQEX_KineDriver_Component::CopyFromSkeletalMeshAssetUserData() {
}


