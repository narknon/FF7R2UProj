#include "EndAnimationSettingsToroccoMiniGame.h"

FEndAnimationSettingsToroccoMiniGame::FEndAnimationSettingsToroccoMiniGame() {
    this->bEnableToroccoRoll = false;
    this->RollSensitivity = 0.00f;
    this->RollInterpSpeed = 0.00f;
    this->MaxRollAngle = 0.00f;
    this->RollBackToleranceAngle = 0.00f;
    this->RollBackDuration = 0.00f;
    this->RollBackOvershootSize = 0.00f;
    this->RollBackOvershootDuration = 0.00f;
    this->bEnableToroccoBonamikWind = false;
    this->MaxBonamikWindPower = 0.00f;
    this->ConstantBonamikWindPower = 0.00f;
    this->BonamikWindPropotionalSpeed = 0.00f;
    this->bEnableToroccoShaking = false;
    this->bEnableBoneControl = false;
    this->BoneControlSensitivity = 0.00f;
    this->BoneControlInterpSpeed = 0.00f;
    this->BoneControlDelay = 0.00f;
    this->BoneControlBarretMaxWeightShiftRight = 0.00f;
    this->BoneControlBarretMaxWeightShiftLeft = 0.00f;
    this->BoneControlYuffieMaxWeightShiftRight = 0.00f;
    this->BoneControlYuffieMaxWeightShiftLeft = 0.00f;
    this->BoneControlTifaMaxWeightShiftRight = 0.00f;
    this->BoneControlTifaMaxWeightShiftLeft = 0.00f;
    this->BoneControlBarretMaxTilt = 0.00f;
    this->BoneControlYuffieMaxTilt = 0.00f;
    this->BoneControlTifaMaxTilt = 0.00f;
}

