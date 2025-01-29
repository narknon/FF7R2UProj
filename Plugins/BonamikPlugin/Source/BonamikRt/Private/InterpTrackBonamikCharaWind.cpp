#include "InterpTrackBonamikCharaWind.h"
#include "InterpTrackInstBonamikCharaWind.h"

UInterpTrackBonamikCharaWind::UInterpTrackBonamikCharaWind() {
    this->TrackInstClass = UInterpTrackInstBonamikCharaWind::StaticClass();
    this->TrackTitle = TEXT("BonamikCharaWind");
    this->m_BaseStrength = 100.00f;
    this->m_WaveAmplitude = 0.00f;
    this->m_WavePeriod = 0.00f;
}


