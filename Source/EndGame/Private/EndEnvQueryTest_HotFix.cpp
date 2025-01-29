#include "EndEnvQueryTest_HotFix.h"

UEndEnvQueryTest_HotFix::UEndEnvQueryTest_HotFix() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->HotFixType = EEndQueryTestHotFixType::None;
}


