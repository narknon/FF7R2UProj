#include "EndPlayerLeaderActionParamComponent.h"

UEndPlayerLeaderActionParamComponent::UEndPlayerLeaderActionParamComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bAutoActivate = true;
    this->bNewDebugMove = false;
    this->bFieldNewJumpMode = false;
}


