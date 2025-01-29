#include "EndDataTableBattleEnemyCombinationAbility.h"

FEndDataTableBattleEnemyCombinationAbility::FEndDataTableBattleEnemyCombinationAbility() {
    this->CombinationType = 0;
    this->ExecutionConditionType = 0;
    this->DashCancelDistance = 0.00f;
    this->LoopAbilities = 0;
    this->MainCancelConditionAbilityMiss = 0;
    this->SubCancelConditionAbilityMiss = 0;
    this->CancelPercentHP = 0.00f;
    this->CancelConditionBurst = 0;
    this->ContinueOnSinglePartyMember = 0;
    this->ForceTargetLeader = 0;
    this->EnableTargetDirectionCorrection = 0;
}

