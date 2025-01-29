#include "SummonAbilityChoice.h"

FSummonAbilityChoice::FSummonAbilityChoice() {
    this->Priority = 0;
    this->MinDistance = 0.00f;
    this->MaxDistance = 0.00f;
    this->MinHeight = 0.00f;
    this->MaxHeight = 0.00f;
    this->InfluenceCenter = ESummonAbilityInfluenceCenter::eNone;
    this->InfluenceRadius = 0.00f;
    this->InfluenceTargets = 0;
    this->SelfToGroundDist = 0.00f;
    this->TargetToGroundDist = 0.00f;
    this->Probability = 0.00f;
    this->MinAttackRange = 0.00f;
    this->MaxAttackRange = 0.00f;
}

