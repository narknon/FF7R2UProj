#include "EndEnvQueryTest_AsyncTrace.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

UEndEnvQueryTest_AsyncTrace::UEndEnvQueryTest_AsyncTrace() {
    this->TestPurpose = EEnvTestPurpose::Filter;
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->Context = UEnvQueryContext_Querier::StaticClass();
    this->TraceShape = EEnvTraceShape::Line;
    this->bOffsetOnlyAffectsItems = false;
}


