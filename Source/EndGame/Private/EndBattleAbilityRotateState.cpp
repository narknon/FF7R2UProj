#include "EndBattleAbilityRotateState.h"

UEndBattleAbilityRotateState::UEndBattleAbilityRotateState() {
    this->Type = EBattleAbilityRotateNotifyState::None;
    this->GoalAngle = 0.00f;
    this->FrameDeltaTimeSpeed = 1.00f;
    this->bKeepRotateAfterInterrupted = false;
}


