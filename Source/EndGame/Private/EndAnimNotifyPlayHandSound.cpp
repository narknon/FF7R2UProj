#include "EndAnimNotifyPlayHandSound.h"

UEndAnimNotifyPlayHandSound::UEndAnimNotifyPlayHandSound() {
    this->HandSocketName = TEXT("R_Hand_a");
    this->SwitchValue = 0.00f;
    this->ZeroOneSlotIndex = -1;
    this->ZeroOneValue = 0.00f;
    this->bSyncOwnerHiddenState = true;
    this->bDirectAssignFootAttribute = false;
    this->DirectAssignFootAttribute = EEndFootAttributeTypes::None;
}


