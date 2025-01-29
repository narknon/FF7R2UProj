#include "EndEnvQueryTest_Follow_CheckPositionType.h"

UEndEnvQueryTest_Follow_CheckPositionType::UEndEnvQueryTest_Follow_CheckPositionType() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->m_PositionType = EEndAIFollowPosition::FORWARD;
}


