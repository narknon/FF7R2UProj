#include "EndBehaviorJumpExtraActionInput.h"

FEndBehaviorJumpExtraActionInput::FEndBehaviorJumpExtraActionInput() {
    this->OverrideBeginSequence = NULL;
    this->OverrideLoopSequence = NULL;
    this->OverrideEndSequence = NULL;
    this->OverrideRunEndSequence = NULL;
    this->bUseRunEndSequence = false;
    this->bAbstractSequence = false;
    this->OverrideGravityScale = 0.00f;
    this->BeginSequenceStartTime = 0.00f;
    this->bForceJump = false;
    this->bSkipRunEndSequence = false;
}

