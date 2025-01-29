#include "EndEnvQueryTest_SwimSplineMovementRestriction.h"

UEndEnvQueryTest_SwimSplineMovementRestriction::UEndEnvQueryTest_SwimSplineMovementRestriction() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->m_bLeaderSwimming = true;
}


