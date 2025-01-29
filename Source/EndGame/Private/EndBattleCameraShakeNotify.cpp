#include "EndBattleCameraShakeNotify.h"

UEndBattleCameraShakeNotify::UEndBattleCameraShakeNotify() {
    this->Cycle = 1.00f;
    this->Power = 1.00f;
    this->Decay = 0.00f;
    this->BlendInTime = 0.00f;
    this->BlendOutTime = 0.50f;
    this->Inner = 100.00f;
    this->Outer = 5000.00f;
    this->Duration = 1.00f;
    this->CombinationCharacter = false;
}


