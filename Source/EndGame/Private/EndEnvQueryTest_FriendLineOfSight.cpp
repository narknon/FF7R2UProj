#include "EndEnvQueryTest_FriendLineOfSight.h"

UEndEnvQueryTest_FriendLineOfSight::UEndEnvQueryTest_FriendLineOfSight() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->ConsiderCheckOnNavmesh = true;
}


