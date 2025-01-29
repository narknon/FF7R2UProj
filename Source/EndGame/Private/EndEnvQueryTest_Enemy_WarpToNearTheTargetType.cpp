#include "EndEnvQueryTest_Enemy_WarpToNearTheTargetType.h"

UEndEnvQueryTest_Enemy_WarpToNearTheTargetType::UEndEnvQueryTest_Enemy_WarpToNearTheTargetType() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->WarpType = EEndAIMoveDefWarpToNearTheTargetType::NearSelf;
}


