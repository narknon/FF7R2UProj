#include "EndFieldActionTinyBroncoSplineMoveActionData.h"

FEndFieldActionTinyBroncoSplineMoveActionData::FEndFieldActionTinyBroncoSplineMoveActionData() {
    this->InputKey = 0.00f;
    this->ActionType = EEndFieldActionTinyBroncoSplineMoveActionType::StableMove;
    this->bDisableResetPeriodicMove = false;
    this->UpwardOffset = 0.00f;
    this->InvalidInputTime = 0.00f;
    this->MaxSpeedScale = 0.00f;
}

