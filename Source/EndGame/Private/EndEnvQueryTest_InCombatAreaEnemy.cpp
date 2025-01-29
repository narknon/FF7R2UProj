#include "EndEnvQueryTest_InCombatAreaEnemy.h"

UEndEnvQueryTest_InCombatAreaEnemy::UEndEnvQueryTest_InCombatAreaEnemy() {
    this->TestPurpose = EEnvTestPurpose::Filter;
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
}


