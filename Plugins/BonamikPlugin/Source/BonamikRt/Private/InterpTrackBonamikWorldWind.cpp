#include "InterpTrackBonamikWorldWind.h"
#include "InterpTrackInstBonamikWorldWind.h"

UInterpTrackBonamikWorldWind::UInterpTrackBonamikWorldWind() {
    this->TrackInstClass = UInterpTrackInstBonamikWorldWind::StaticClass();
    this->TrackTitle = TEXT("BonamikWorldWind");
    this->m_BonamikWindGlobalAddition = true;
    this->m_SphereRadius = 500.00f;
    this->m_AreaMargin = 0.00f;
    this->m_RandomTime = 1.00f;
    this->m_BlastStrength = 100.00f;
    this->m_PeakInRange = 0.50f;
    this->m_BlastRange = 100.00f;
    this->m_BlastSpeed = 100.00f;
    this->m_LoopNum = 1;
    this->m_StartFrame = 0;
}


