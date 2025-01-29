#include "EndAIControllerAnimalBase.h"

AEndAIControllerAnimalBase::AEndAIControllerAnimalBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->Animal_CautionDistance = 1500.00f;
    this->Animal_SenseDistance = 1000.00f;
    this->Animal_EscapeDistance = 500.00f;
    this->Animal_WanderingRadius = 2000.00f;
    this->Animal_WaitTime = 10.00f;
    this->Animal_WaitTimeRandom = 0.00f;
}


