#include "EndBTDecorator_CompareTargetPropertyResist.h"

UEndBTDecorator_CompareTargetPropertyResist::UEndBTDecorator_CompareTargetPropertyResist() {
    this->NodeName = TEXT("[End][AIPC]CompareTargetPropertyResist");
    this->Operator = EEndAiMathCmp::Equal;
    this->PropertyTypeA = EAIPCDamagePropertyFlag::None;
    this->PropertyTypeB = EAIPCDamagePropertyFlag::None;
}


