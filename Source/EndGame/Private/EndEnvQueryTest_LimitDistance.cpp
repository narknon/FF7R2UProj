#include "EndEnvQueryTest_LimitDistance.h"

UEndEnvQueryTest_LimitDistance::UEndEnvQueryTest_LimitDistance() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->m_Context = NULL;
}


