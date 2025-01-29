#include "GoalData.h"

FGoalData::FGoalData() {
    this->GoalOwner = ETeamType::TeamA;
    this->GoalBox = NULL;
    this->GravityBox = NULL;
    this->GoalScore = 0;
}

