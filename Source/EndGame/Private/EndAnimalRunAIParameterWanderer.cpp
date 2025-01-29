#include "EndAnimalRunAIParameterWanderer.h"

UEndAnimalRunAIParameterWanderer::UEndAnimalRunAIParameterWanderer() {
    this->bOverrideRestTime = false;
    this->RestTime = 5.00f;
    this->bOverrideRestTimeMax = false;
    this->RestTimeMax = 10.00f;
    this->bOverrideMoveRangeRadius = false;
    this->MoveRangeRadius = 800.00f;
    this->bOverrideRestMotionBegin = false;
    this->bOverrideRestMotionLoop = false;
    this->bOverrideRestMotionEnd = false;
    this->bOverridebSearchNearRestPoint = false;
    this->bSearchNearRestPoint = false;
    this->bOverridebCanRunIfFar = false;
    this->bCanRunIfFar = false;
}


