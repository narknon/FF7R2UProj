#include "EndBTDecorator_MiniGameRunWildCheckAngle.h"

UEndBTDecorator_MiniGameRunWildCheckAngle::UEndBTDecorator_MiniGameRunWildCheckAngle() {
    this->NodeName = TEXT("[End][MiniGame]RunWildCheckAngle");
    this->A = EEndAnimalRunAngleType::OwnerForward;
    this->B = EEndAnimalRunAngleType::OwnerForward;
    this->Operator = EEndAiMathCmp::Equal;
    this->Angle = 30.00f;
}


