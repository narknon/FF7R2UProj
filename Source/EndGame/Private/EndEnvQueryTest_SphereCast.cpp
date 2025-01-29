#include "EndEnvQueryTest_SphereCast.h"

UEndEnvQueryTest_SphereCast::UEndEnvQueryTest_SphereCast() {
    this->TestPurpose = EEnvTestPurpose::Filter;
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->TestType = EEndTestSphereCast::Test2D;
    this->Center = NULL;
    this->TargetContext = NULL;
    this->CastRadius = 50.00f;
    this->TargetRadius = 50.00f;
}


