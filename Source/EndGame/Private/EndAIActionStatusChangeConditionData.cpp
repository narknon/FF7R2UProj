#include "EndAIActionStatusChangeConditionData.h"

FEndAIActionStatusChangeConditionData::FEndAIActionStatusChangeConditionData() {
    this->LogicalOperator = EEndAILogicalOperator::AND;
    this->bNot = false;
}

