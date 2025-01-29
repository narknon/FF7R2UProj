#include "EndBehaviorTargetJumpExtraActionInput.h"

FEndBehaviorTargetJumpExtraActionInput::FEndBehaviorTargetJumpExtraActionInput() {
    this->RootLocationTargetActor = NULL;
    this->bSetRotation = false;
    this->RootRotationTargetActor = NULL;
    this->RotationInterpSpeed = 0.00f;
    this->JumpAngle = 0.00f;
    this->JumpHeightMax = 0.00f;
    this->JumpTimeMin = 0.00f;
    this->bLandingWithTimer = false;
    this->bDisableHitEnvResponse = false;
    this->bSetMovementJumpTimeMax = false;
    this->bUseLoopSequenceAsOneShot = false;
}

