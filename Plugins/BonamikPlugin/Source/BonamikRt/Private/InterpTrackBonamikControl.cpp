#include "InterpTrackBonamikControl.h"
#include "InterpTrackInstBonamikControl.h"

UInterpTrackBonamikControl::UInterpTrackBonamikControl() {
    this->TrackInstClass = UInterpTrackInstBonamikControl::StaticClass();
    this->TrackTitle = TEXT("BonamikControl");
    this->m_Reset = false;
    this->m_PreRoll = 0;
    this->m_PreRollForAttachment = 0;
    this->m_bBlendedWeight = false;
}


