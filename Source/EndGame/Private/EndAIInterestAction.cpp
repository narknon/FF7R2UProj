#include "EndAIInterestAction.h"

FEndAIInterestAction::FEndAIInterestAction() {
    this->bUpdatableWhenAIStop = false;
    this->Priority = EEndAIIntentionPriority::RuleBased;
    this->CurrentState = EEndAIInterestActionState::Pending;
    this->Index = 0;
}

