#include "EndEnvQueryTest_NavmeshDistanceRatio.h"

UEndEnvQueryTest_NavmeshDistanceRatio::UEndEnvQueryTest_NavmeshDistanceRatio() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->Center = NULL;
    this->QueryFilterType = EEndQueryFilterType::Default;
    this->NavAgentPropertyCategory = ENavAgentPropertyCategory::Default;
    this->bLongDistanceIfFail = false;
    this->bItemProjection = false;
    this->bPermitNavLink = false;
}


