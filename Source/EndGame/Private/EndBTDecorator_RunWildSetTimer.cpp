#include "EndBTDecorator_RunWildSetTimer.h"

UEndBTDecorator_RunWildSetTimer::UEndBTDecorator_RunWildSetTimer() {
    this->NodeName = TEXT("[End][MiniGame]RunWildSetTimer");
    this->Type = EEndAnimalRunTimerType::Rest;
    this->bStop = false;
}


