#include "EndAIActionPackTransInfo.h"

FEndAIActionPackTransInfo::FEndAIActionPackTransInfo() {
    this->ActionDefinitionClass = NULL;
    this->PrimaryAnimPackIgnoreLowerPriority = false;
    this->bNotifyTrans = false;
    this->bCanLookAt = EEndAIStateParamBool::FalseFlag;
    this->bCanTurn = EEndAIStateParamBool::FalseFlag;
}

