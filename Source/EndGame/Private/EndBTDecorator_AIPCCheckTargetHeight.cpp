#include "EndBTDecorator_AIPCCheckTargetHeight.h"

UEndBTDecorator_AIPCCheckTargetHeight::UEndBTDecorator_AIPCCheckTargetHeight() {
    this->NodeName = TEXT("[End][AIPC]CheckTargetHeight");
    this->TargetType = ETargetType::Normal;
    this->Operator = EEndAiMathCmp::Equal;
    this->Height = 0.00f;
    this->bUseBBKey = false;
}


