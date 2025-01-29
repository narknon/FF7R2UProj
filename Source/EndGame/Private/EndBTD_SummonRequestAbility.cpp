#include "EndBTD_SummonRequestAbility.h"

UEndBTD_SummonRequestAbility::UEndBTD_SummonRequestAbility() {
    this->NodeName = TEXT("[End]SummonRequestAbility");
    this->bIgnoreAbilityRange = false;
    this->AbilityRange = 0.00f;
    this->bUseDefaultAbilityRange = false;
    this->RequestAbilityIDBlackBoardName = TEXT("RequestAbilityID");
    this->AbilityRangeBlackBoardName = TEXT("AbilityRange");
    this->IgnoreAbilityRangeBlackBoardName = TEXT("IgnoreAbilityRange");
    this->AbilityLockBlackBoardName = TEXT("AbilityLock");
}


