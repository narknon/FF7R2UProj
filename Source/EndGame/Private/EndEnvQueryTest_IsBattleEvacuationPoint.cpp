#include "EndEnvQueryTest_IsBattleEvacuationPoint.h"

UEndEnvQueryTest_IsBattleEvacuationPoint::UEndEnvQueryTest_IsBattleEvacuationPoint() {
    this->TestPurpose = EEnvTestPurpose::Filter;
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
}


