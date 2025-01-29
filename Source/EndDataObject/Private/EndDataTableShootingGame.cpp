#include "EndDataTableShootingGame.h"

FEndDataTableShootingGame::FEndDataTableShootingGame() {
    this->Timelimit = 0.00f;
    this->FireInterval = 0.00f;
    this->CursolSpeed = 0.00f;
    this->CursolOffsetSpeed = 0.00f;
    this->CameraOffsetYawLimit = 0.00f;
    this->CameraOffsetPitchLimit = 0.00f;
    this->CameraOffsetFOV = 0.00f;
    this->CursolShakeOffsetMaxX = 0.00f;
    this->CursolShakeOffsetMinX = 0.00f;
    this->CursolShakeOffsetMaxY = 0.00f;
    this->CursolShakeOffsetMinY = 0.00f;
    this->CursolShakeOffsetSpeed = 0.00f;
    this->EnduranceCountDrawTime = 0.00f;
    this->FailureTime = 0.00f;
    this->FailureShotCount = 0;
    this->SpecialResultScore = 0;
    this->GoldGoalScore = 0;
    this->SilverGoalScore = 0;
    this->CopperGoalScore = 0;
}

