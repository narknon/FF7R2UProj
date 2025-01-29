#include "EndAIControllerFriendBase.h"

AEndAIControllerFriendBase::AEndAIControllerFriendBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->GroundTargetReachableHeight = 300.00f;
    this->AirTargetReachableHeight = 500.00f;
    this->bDoRangedAttack = false;
    this->bCanStrafeMove = true;
    this->bCanGuard = false;
    this->BattleCautionType = EFriendBattleCautionType::KeepMoving;
    this->BattleCautionMoveType = EEndAiMoveType::WALK;
    this->BattleCautionLeaderDistance = 0.00f;
    this->BattleCautionFriendDistance = 0.00f;
    this->HardAttackFrequency = 0;
    this->ToadBattleParam = NULL;
    this->StandbyTimeMax = 2.00f;
    this->StandbyTimeMin = 1.00f;
}

bool AEndAIControllerFriendBase::RequestAbility(FName AbilityId, EFriendAbilityTargetType TargetType, bool bPriority, AEndCharacter* Target, FName prevComboAbilityId, bool bRetryFailed) {
    return false;
}

void AEndAIControllerFriendBase::OverrideCooldownTimer(float Time, bool bForce) {
}






