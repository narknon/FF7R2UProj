#include "EndDataTableBikeAbility.h"

FEndDataTableBikeAbility::FEndDataTableBikeAbility() {
    this->AbilityType = 0;
    this->NormalRange = 0;
    this->DistanceType = 0;
    this->CoolDownTime = 0.00f;
    this->ExclusiveGroup = 0;
    this->TargetToPlayerOdds = 0;
    this->TargetToAllyOdds = 0;
    this->AttackerPositionCondition = 0;
    this->CenterPositionOffset = 0.00f;
    this->TargetPositionCondition = 0;
    this->TargetSearchDistanceMin = 0.00f;
    this->TargetSearchDistanceMax = 0.00f;
    this->TargetSearchDiffSplineMileageMin = 0.00f;
    this->TargetSearchDiffSplineMileageMax = 0.00f;
    this->SuperArmorSincePrepare = 0;
    this->ShowAttackLineEffect = 0;
    this->NotCancelAtOutOfRange = 0;
    this->DisableSlideMoveOnAttacking = 0;
    this->PrepareAttackTimeout = 0.00f;
    this->ForceAttackTime = 0.00f;
    this->BurstDamageBonus = 0.00f;
}

