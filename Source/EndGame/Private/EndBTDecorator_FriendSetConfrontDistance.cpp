#include "EndBTDecorator_FriendSetConfrontDistance.h"

UEndBTDecorator_FriendSetConfrontDistance::UEndBTDecorator_FriendSetConfrontDistance() {
    this->NodeName = TEXT("[End][Friend]SetConfrontDistance");
    this->ConfrontType = EConfrontType::COMBAT;
    this->MinDistance = 0.00f;
    this->MaxDistance = 99999.00f;
    this->Offset = 0.00f;
    this->bUseBBKeyOffset = false;
    this->bInverseOffset = false;
}


