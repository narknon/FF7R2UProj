#include "EndBTDecorator_AIPCCheckTargetAngle.h"

UEndBTDecorator_AIPCCheckTargetAngle::UEndBTDecorator_AIPCCheckTargetAngle() {
    this->NodeName = TEXT("[End][AIPC]CheckTargetAngle");
    this->TargetType = ETargetType::Normal;
    this->SpecifiedAngle = 0.00f;
}


