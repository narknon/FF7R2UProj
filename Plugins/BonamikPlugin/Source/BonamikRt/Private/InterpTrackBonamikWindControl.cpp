#include "InterpTrackBonamikWindControl.h"
#include "InterpTrackInstBonamikWindControl.h"

UInterpTrackBonamikWindControl::UInterpTrackBonamikWindControl() {
    this->TrackInstClass = UInterpTrackInstBonamikWindControl::StaticClass();
    this->TrackTitle = TEXT("BonamikWindControl");
}


