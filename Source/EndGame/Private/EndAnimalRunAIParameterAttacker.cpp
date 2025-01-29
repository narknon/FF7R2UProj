#include "EndAnimalRunAIParameterAttacker.h"

UEndAnimalRunAIParameterAttacker::UEndAnimalRunAIParameterAttacker() {
    this->TargetSelectionPriorityList.AddDefaulted(1);
    this->bOverrideAttackerRestTime = false;
    this->AttackerRestTime = 3.00f;
    this->bOverrideAttackerRestTimeMax = false;
    this->AttackerRestTimeMax = 3.00f;
    this->bOverrideChasingTime = false;
    this->ChasingTime = 6.00f;
    this->bOverrideChasingTimeMax = false;
    this->ChasingTimeMax = 6.00f;
    this->bOverrideAttackerStopChaseDistance = false;
    this->AttackerStopChaseDistance = 200.00f;
}


