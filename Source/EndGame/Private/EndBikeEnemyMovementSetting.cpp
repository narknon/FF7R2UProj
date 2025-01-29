#include "EndBikeEnemyMovementSetting.h"

UEndBikeEnemyMovementSetting::UEndBikeEnemyMovementSetting() {
    this->StartApproachSlideLength = 800.00f;
    this->EndApproachSlideLength = 500.00f;
    this->StartLeaveFromWallLength = 150.00f;
    this->EndLeaveFromWallLength = 300.00f;
    this->FollowPlayerTime = 5.00f;
    this->ReEnterFollowPlayerInvalidTime = 2.00f;
    this->WithdrawalForwardRate = 0.00f;
    this->PendingWithdrawalTimeIfPlayerBoostAccel = 5.00f;
    this->SPformGroupRelativePositionList.AddDefaulted(8);
    this->BSformGroupRelativePositionList.AddDefaulted(8);
    this->BSformBaseForwardOffset = 1200.00f;
    this->BSformMinForwardOffset = 400.00f;
    this->BSformDesireMaxSpeed = 178.00f;
    this->BSformKeepBaseForwardOffsetTime = 0.00f;
    this->BSformRelativeSpeedOnAccel = 20.00f;
    this->BSformRelativeSpeedOnNeutral = 0.00f;
    this->BSformRelativeSpeedOnBrake = 40.00f;
    this->EnableCancelEntryMaxNum = 2;
    this->EnableCancelEntryNumPerumoEnemies = 4;
    this->EnableCancelEntryDistance = -600.00f;
    this->CancelEntryEndTime = -1.00f;
}


