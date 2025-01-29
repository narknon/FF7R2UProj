#include "EndMobPrefabAutoReactionExecuteCommand.h"

UEndMobPrefabAutoReactionExecuteCommand::UEndMobPrefabAutoReactionExecuteCommand() {
    this->DistanceThreshold = 0.00f;
    this->AngleThreshold = 0.00f;
    this->HeightThreshold = 0.00f;
    this->ContinuationTime = 0.00f;
    this->bFromCenter = false;
    this->bReactionToParty = true;
    this->bLookAway = false;
    this->InBlendTime = 0.00f;
    this->OutBlendTime = 0.00f;
    this->bPlayMotionOnce = false;
}


