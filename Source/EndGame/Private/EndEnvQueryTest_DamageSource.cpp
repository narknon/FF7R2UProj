#include "EndEnvQueryTest_DamageSource.h"

UEndEnvQueryTest_DamageSource::UEndEnvQueryTest_DamageSource() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->Type = EEnvQueryTest_DamageSource_AffectedType::Player;
}


