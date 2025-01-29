#include "EndBattleCameraShakeNotifyState.h"

UEndBattleCameraShakeNotifyState::UEndBattleCameraShakeNotifyState() {
    this->Cycle = 1.00f;
    this->Power = 1.00f;
    this->Decay = 0.00f;
    this->BlendInTime = 0.00f;
    this->BlendOutTime = 0.50f;
    this->Inner = 100.00f;
    this->Outer = 5000.00f;
    this->EnableLoop = false;
    this->CombinationCharacter = false;
}


