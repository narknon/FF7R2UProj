#include "EndBTDecorator_TimeLimit.h"

UEndBTDecorator_TimeLimit::UEndBTDecorator_TimeLimit() {
    this->bUseBBMinTime = false;
    this->bUseBBMaxTime = false;
    this->MinTime = 5.00f;
    this->MaxTime = 5.00f;
    this->bWriteBB = false;
}


