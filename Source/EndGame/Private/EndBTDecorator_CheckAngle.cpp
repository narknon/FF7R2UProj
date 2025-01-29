#include "EndBTDecorator_CheckAngle.h"

UEndBTDecorator_CheckAngle::UEndBTDecorator_CheckAngle() {
    this->UseSourceToBlackboard = false;
    this->Operator = EEndAiMathCmp::Less;
    this->bUseBlackboardAngle = false;
    this->CheckAngle = 45.00f;
    this->bAbs = false;
    this->bCheckDeltaYaw = false;
}


