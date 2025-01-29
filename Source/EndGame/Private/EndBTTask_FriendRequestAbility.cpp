#include "EndBTTask_FriendRequestAbility.h"

UEndBTTask_FriendRequestAbility::UEndBTTask_FriendRequestAbility() {
    this->NodeName = TEXT("[End][Friend]RequestAbility");
    this->AbilityType = EFriendAbilityType::NormalAttack;
    this->TargetType = EFriendAbilityTargetType::BattleTarget;
    this->TimeOut = 1.50f;
}


