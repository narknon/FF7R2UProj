#include "EndAnimalRunAIParameterGoalKeeper.h"

UEndAnimalRunAIParameterGoalKeeper::UEndAnimalRunAIParameterGoalKeeper() {
    this->bOverrideGoalKeeperSearchRangeRadius = false;
    this->GoalKeeperSearchRangeRadius = 1000.00f;
    this->bOverrideGoalKeeperRestTime = false;
    this->GoalKeeperRestTime = 5.00f;
    this->bOverrideGoalKeeperRestTimeMax = false;
    this->GoalKeeperRestTimeMax = 5.00f;
    this->bOverrideGoalKeeperMoveRangeRadius = false;
    this->GoalKeeperMoveRangeRadius = 800.00f;
    this->bOverrideGoalKeeperCanShoot = false;
    this->GoalKeeperCanShoot = false;
    this->bOverrideGoalKeeperRestTimeAfterShoot = false;
    this->GoalKeeperRestTimeAfterShoot = 1.00f;
}


