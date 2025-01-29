#include "EndAIMoveDefinitionZigzagStep.h"

UEndAIMoveDefinitionZigzagStep::UEndAIMoveDefinitionZigzagStep() {
    this->bNotActionInterrupt = true;
    this->AccessLength = 800.00f;
    this->MoveDefinitionStepRightClass = NULL;
    this->MoveDefinitionStepLeftClass = NULL;
    this->AddFrontDirc = 1.00f;
    this->StepCountMin = 2;
    this->StepCountMax = 4;
}


