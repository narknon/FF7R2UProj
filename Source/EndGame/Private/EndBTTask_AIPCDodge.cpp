#include "EndBTTask_AIPCDodge.h"

UEndBTTask_AIPCDodge::UEndBTTask_AIPCDodge() {
    this->NodeName = TEXT("[End][AIPC]Dodge");
    this->DodgeDirectionType = EDodgeDirectionType::TOWARD;
    this->StartWaitTime = 0.10f;
    this->bInputDirectionDuringDodge = true;
    this->bStyleChange = false;
}


