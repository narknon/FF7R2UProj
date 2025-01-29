#include "InterpTrackBonamikTeleport.h"
#include "InterpTrackInstBonamikTeleport.h"

UInterpTrackBonamikTeleport::UInterpTrackBonamikTeleport() {
    this->TrackInstClass = UInterpTrackInstBonamikTeleport::StaticClass();
    this->TrackTitle = TEXT("BonamikTeleport");
    this->bOnePerGroup = true;
}


