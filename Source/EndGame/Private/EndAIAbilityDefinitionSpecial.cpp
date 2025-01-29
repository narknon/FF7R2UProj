#include "EndAIAbilityDefinitionSpecial.h"

UEndAIAbilityDefinitionSpecial::UEndAIAbilityDefinitionSpecial() {
    this->NotMoveTime_Enemy = 0.00f;
    this->ActionAfterInterval_Enemy = 0.00f;
    this->bDisableSelfIdleReset = false;
    this->bDisablePlayerIdleReset = false;
    this->bDisableCombiIdleReset = false;
    this->bDisableSelfIdleReset_Combo = true;
    this->bDisablePlayerIdleReset_Combo = true;
    this->bDisableOtherIdleReset_Combo = true;
}


