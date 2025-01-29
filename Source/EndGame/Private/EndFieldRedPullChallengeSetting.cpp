#include "EndFieldRedPullChallengeSetting.h"

FEndFieldRedPullChallengeSetting::FEndFieldRedPullChallengeSetting() {
    this->Type = EEndFieldRedPullChallengeSettingType::Normal;
    this->ChallengeTime = 0.00f;
    this->ChallengeDistance = 0.00f;
    this->bEnemyLeftPullButton = false;
    this->bEnemyRightPullButton = false;
    this->EnemyLeftPullButtonRandomPerRate = 0.00f;
    this->EnemyLeftPullRandomChangeMinTime = 0.00f;
    this->EnemyLeftPullRandomChangeMaxTime = 0.00f;
    this->EnemyRightPullButtonRandomPerRate = 0.00f;
    this->EnemyRightPullRandomChangeMinTime = 0.00f;
    this->EnemyRightPullRandomChangeMaxTime = 0.00f;
    this->EnemyLeftMotionRate = 0.00f;
    this->EnemyRightMotionRate = 0.00f;
    this->PlayerMotionRate = 0.00f;
    this->InputEnemyLeftMotionRate = 0.00f;
    this->InputEnemyRightMotionRate = 0.00f;
    this->InputPlayerMotionRate = 0.00f;
    this->FailedEnemyLeftMotionRate = 0.00f;
    this->FailedEnemyRightMotionRate = 0.00f;
    this->FailedPlayerMotionRate = 0.00f;
    this->SuccessIdleTimeMax = 0.00f;
    this->SuccessToNextIntervalTime = 0.00f;
    this->FaildToNextIntervalTime = 0.00f;
}

