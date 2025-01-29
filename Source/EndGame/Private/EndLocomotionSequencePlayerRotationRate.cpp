#include "EndLocomotionSequencePlayerRotationRate.h"

FEndLocomotionSequencePlayerRotationRate::FEndLocomotionSequencePlayerRotationRate() {
    this->BehaviorMode = EEndAnimBehaviorMode::Neutral;
    this->LocomotionState = EEndLocomotionState::Idle;
    this->RotationRate = 0.00f;
}

