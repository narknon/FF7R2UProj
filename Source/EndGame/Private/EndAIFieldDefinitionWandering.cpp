#include "EndAIFieldDefinitionWandering.h"

UEndAIFieldDefinitionWandering::UEndAIFieldDefinitionWandering() {
    this->RangeRadius = 1000.00f;
    this->StayTime = 5.00f;
    this->StayTimeWidth = 5.00f;
    this->bPlayStandardIdle = true;
    this->bPlayLookAroundIdle = true;
    this->RestartInterval = 3.00f;
    this->RestartIntervalWidth = 2.00f;
    this->MoveTimeOut = 10.00f;
}


