#include "RenoMineMovementData.h"

FRenoMineMovementData::FRenoMineMovementData() {
    this->MovementMode = ERenoMineMovementMode::NONE;
    this->MineMaxSpeed = 0.00f;
    this->MineSnapSpeed = 0.00f;
    this->MineSnapEndQuantity = 0.00f;
    this->RenoDistance = 0.00f;
    this->UcpcDistance = 0.00f;
    this->RepulsiveDistance = 0.00f;
    this->RepulsiveAccQuantity = 0.00f;
    this->MineMoveInterval = 0.00f;
    this->RepulsiveOriginInterval = 0.00f;
    this->bCanFollow = false;
    this->bCanRollingAtack = false;
    this->RollingAtackStartDistance = 0.00f;
    this->RollingAtackPhase1Time = 0.00f;
    this->RollingAtackPhase1Height = 0.00f;
    this->RollingAtackSpeed = 0.00f;
    this->RollingAtackRadius = 0.00f;
    this->RollingAtackFinish = 0.00f;
    this->ReturnSpeed = 0.00f;
    this->TurnSpeed = 0.00f;
}

