#include "EndAIActionTransAttackInterval.h"

FEndAIActionTransAttackInterval::FEndAIActionTransAttackInterval() {
    this->IntervalType = EEndAIIntervalType::LightAttack;
    this->bDefault = false;
    this->Interval = 0.00f;
    this->IntervalWidth = 0.00f;
}

