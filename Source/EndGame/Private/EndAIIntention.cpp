#include "EndAIIntention.h"

FEndAIIntention::FEndAIIntention() {
    this->bUpdatableWhenAIStop = false;
    this->Priority = EEndAIIntentionPriority::RuleBased;
}

