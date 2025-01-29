#include "SQEX_BonamikPossessionDesc_v2.h"

FSQEX_BonamikPossessionDesc_v2::FSQEX_BonamikPossessionDesc_v2() {
    this->m_BodyId = 0;
    this->m_Time = 0.00f;
    this->m_Mode = ESQEX_Bonamik_PSSMODE_v2_SWING_Y;
    this->m_SubMode = 0;
    this->m_IsFlow = false;
    this->m_DrawingRadius = 0.00f;
    this->m_TimeToActivateNext = 0.00f;
    this->m_Magnitude = 0.00f;
    this->m_IncrementalMagnitude = 0.00f;
    this->m_MaxMagnitude = 0.00f;
    this->m_DelayTime = 0.00f;
}

