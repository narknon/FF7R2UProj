#include "EndLocomotionBlendSpacePlayerRotationRate.h"

FEndLocomotionBlendSpacePlayerRotationRate::FEndLocomotionBlendSpacePlayerRotationRate() {
    this->BehaviorMode = EEndAnimBehaviorMode::Neutral;
    this->LocomotionState = EEndLocomotionState::Idle;
    this->RotationRate = 0.00f;
}

