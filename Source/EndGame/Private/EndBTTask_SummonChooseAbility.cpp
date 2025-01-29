#include "EndBTTask_SummonChooseAbility.h"

UEndBTTask_SummonChooseAbility::UEndBTTask_SummonChooseAbility() {
    this->NodeName = TEXT("[End]SummonChooseAbility");
    this->RequestAbilityIDBlackBoardName = TEXT("RequestAbilityID");
    this->IgnoreAbilityRangeBlackBoardName = TEXT("IgnoreAbilityRange");
    this->AbilityRangeBlackBoardName = TEXT("AbilityRange");
}


