#include "EndAnimInput.h"

FEndAnimInput::FEndAnimInput() {
    this->bPlayerControlled = false;
    this->bEnableMoveInput = false;
    this->bEnableTurnInput = false;
    this->bFixedTurnInput = false;
    this->bEnableDashInput = false;
    this->bEnableStrafingInput = false;
    this->bFlying = false;
    this->bFalling = false;
    this->bSwimming = false;
    this->bSlaveAction = false;
    this->MoveInputSize = 0.00f;
    this->MoveInputDirection = 0.00f;
    this->MoveInputDuration = 0.00f;
    this->TurnInputDirection = 0.00f;
    this->AccelInputSize = 0.00f;
}

