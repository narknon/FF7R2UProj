#include "EndEnvQueryTest_SpacialPathFinding.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

UEndEnvQueryTest_SpacialPathFinding::UEndEnvQueryTest_SpacialPathFinding() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->PathType = EEndTestSpacialPath::Aerial;
    this->TestMode = EEndTestPathfinding::PathExist;
    this->Context = UEnvQueryContext_Querier::StaticClass();
}


