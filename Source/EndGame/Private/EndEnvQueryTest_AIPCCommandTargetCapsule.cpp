#include "EndEnvQueryTest_AIPCCommandTargetCapsule.h"

UEndEnvQueryTest_AIPCCommandTargetCapsule::UEndEnvQueryTest_AIPCCommandTargetCapsule() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->bConsiderOverrideRadius = true;
}


