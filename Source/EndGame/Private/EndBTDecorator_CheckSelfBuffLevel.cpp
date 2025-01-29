#include "EndBTDecorator_CheckSelfBuffLevel.h"

UEndBTDecorator_CheckSelfBuffLevel::UEndBTDecorator_CheckSelfBuffLevel() {
    this->NodeName = TEXT("[End][AIPC]CheckSelfBuffLevel");
    this->Operator = EEndAiMathCmp::Equal;
    this->Level = 0;
    this->bMaxLevel = false;
}


