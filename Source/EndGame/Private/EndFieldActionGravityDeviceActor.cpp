#include "EndFieldActionGravityDeviceActor.h"

AEndFieldActionGravityDeviceActor::AEndFieldActionGravityDeviceActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->m_EventDirection = 0;
    this->m_bStopWarpVFX = false;
    this->m_VFXAssetUserData = NULL;
    this->m_StartInnerDirection = 0;
    this->VFXStartDelaySec = 3.00f;
}


