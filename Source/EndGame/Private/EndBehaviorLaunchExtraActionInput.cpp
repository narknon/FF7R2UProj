#include "EndBehaviorLaunchExtraActionInput.h"

FEndBehaviorLaunchExtraActionInput::FEndBehaviorLaunchExtraActionInput() {
    this->DamageReactionType = EEndBattleDamageSourceHitReactionType::Small;
    this->LaunchWaitTime = 0.00f;
    this->WakeUpTime = 0.00f;
    this->bSkipLaunch = false;
    this->bRotateToLaunchVector = false;
    this->RiseGravityScale = 0.00f;
    this->FallGravityScale = 0.00f;
    this->AirRecoveryWaitTime = 0.00f;
    this->bForceForward = false;
}

