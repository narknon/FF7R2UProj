#include "EndParticleModuleWeaponUpgrade.h"

UEndParticleModuleWeaponUpgrade::UEndParticleModuleWeaponUpgrade() {
    this->bSpawnModule = true;
    this->bUpdateModule = true;
    this->bSupported3DDrawMode = true;
    this->m_DebugMainCoreResource = 0;
    this->m_DebugSubCoreResource = 0;
    this->m_DebugSkillResource = 1;
    this->m_DebugSubCoreCount = 2;
    this->m_DebugMainSkillCount = 5;
    this->m_DebugSubSkillCount = 5;
    this->m_DebugUpgradeCount = 1;
    this->m_DebugPlayStageEffects = false;
    this->m_DebugPlayStageEffectsActive = false;
    this->m_DebugTravelCore = false;
    this->m_DebugTravelTimer = 3.00f;
    this->m_UpgradeScale = 0.50f;
    this->m_WaitCameraMoveTime = 1.00f;
    this->m_WaitStageEffectsTime = 0.50f;
    this->m_WaitCoreStageEffectsTime = 2.50f;
    this->m_CoreStageEffectsFirstDelayTime = 0.50f;
    this->m_CoreStageEffectsDelayTime = 0.20f;
}


