#include "EndBTTask_FriendDodge.h"

UEndBTTask_FriendDodge::UEndBTTask_FriendDodge() {
    this->NodeName = TEXT("[End][Friend]Dodge");
    this->DodgeDirectionType = EDodgeDirectionType::TOWARD;
    this->StartWaitTime = 0.10f;
}


