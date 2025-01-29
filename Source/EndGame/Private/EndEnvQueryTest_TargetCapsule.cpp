#include "EndEnvQueryTest_TargetCapsule.h"

UEndEnvQueryTest_TargetCapsule::UEndEnvQueryTest_TargetCapsule() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->bConsiderOverrideRadius = true;
}


