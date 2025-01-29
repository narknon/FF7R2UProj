#include "VfxParticleModuleCameraControl.h"

UVfxParticleModuleCameraControl::UVfxParticleModuleCameraControl() {
    this->bUpdateModule = true;
    this->bSupported3DDrawMode = true;
    this->m_DebugSetPreviewCamera = false;
    this->m_RefPointName = TEXT("Point_1");
    this->m_BlendTime = 1.00f;
    this->m_BlendExp = 3.00f;
    this->m_EnableGamePad = false;
    this->m_DampingScale = 0.80f;
    this->m_Rstick_RotationSpeed = 60.00f;
    this->m_Rstick_ZoomSpeed = 1000.00f;
    this->m_Rstick_ZoomMin = 150.00f;
    this->m_Rstick_ZoomMax = 3000.00f;
}


