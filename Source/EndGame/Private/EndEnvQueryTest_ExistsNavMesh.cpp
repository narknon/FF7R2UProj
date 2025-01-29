#include "EndEnvQueryTest_ExistsNavMesh.h"

UEndEnvQueryTest_ExistsNavMesh::UEndEnvQueryTest_ExistsNavMesh() {
    this->TestPurpose = EEnvTestPurpose::Filter;
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->QueryFilterType = EEndQueryFilterType::Default;
    this->bApplyDynamicFilter = false;
    this->bPathFindToContext = false;
    this->PathFindTargetContext = NULL;
    this->NavAgentPropertyCategory = ENavAgentPropertyCategory::Default;
}


