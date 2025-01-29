#include "EndAIInterestComponent.h"

FEndAIInterestComponent::FEndAIInterestComponent() {
    this->bActive = false;
    this->bAllowedUpdating = false;
    this->bTeleported = false;
    this->UpdatePriority = EEndAIUpdatePriority::VelyHigh;
    this->DebugDrawBehaviors = false;
}

