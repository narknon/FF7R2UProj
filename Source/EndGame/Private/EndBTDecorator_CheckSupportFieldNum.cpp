#include "EndBTDecorator_CheckSupportFieldNum.h"

UEndBTDecorator_CheckSupportFieldNum::UEndBTDecorator_CheckSupportFieldNum() {
    this->NodeName = TEXT("[End][AIPC]CheckSupportFieldNum");
    this->Operator = EEndAiMathCmp::Equal;
    this->Count = 0;
}


