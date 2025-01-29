#include "SQEX_BonamikWind_Component_v2.h"

UDEPRECATED_SQEX_BonamikWind_Component_v2::UDEPRECATED_SQEX_BonamikWind_Component_v2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bHiddenInGame = true;
    this->m_BonamikWindDesc = NULL;
    this->m_BonamikWindAreaType = ESQEX_Bonamik_WindAreaType_Global;
    this->m_BonamikWindGlobalAddition = true;
    this->m_BonamikWindSphereAreaRadius = 50.00f;
    this->m_BonamikWindAreaMargin = 0.00f;
    this->m_BonamikWindAbsoluteDirection = false;
    this->m_BonamikWindDirectionYaw = 0.00f;
    this->m_BonamikWindDirectionPitch = 0.00f;
    this->m_BonamikWind = NULL;
}

void UDEPRECATED_SQEX_BonamikWind_Component_v2::SetWindScale(float Value) {
}

float UDEPRECATED_SQEX_BonamikWind_Component_v2::GetWindScale() const {
    return 0.0f;
}

void UDEPRECATED_SQEX_BonamikWind_Component_v2::Enable(bool Value) {
}


