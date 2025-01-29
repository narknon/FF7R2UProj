#include "EndBTDecorator_MiniGameRunWildCheckTimerStatus.h"

UEndBTDecorator_MiniGameRunWildCheckTimerStatus::UEndBTDecorator_MiniGameRunWildCheckTimerStatus() {
    this->NodeName = TEXT("[End][MiniGame]RunWildCheckTimerStatus");
    this->Type = EEndAnimalRunTimerType::Rest;
    this->CheckStatusType = EEndRunWildCheckTimerStatusType::IsRunning;
}


