#include "EndEnvQueryTest_AIPCLineOfSight.h"

UEndEnvQueryTest_AIPCLineOfSight::UEndEnvQueryTest_AIPCLineOfSight() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->TargetLocationType = EAIPCTargetLocationType::TargetCursor;
    this->ConsiderWeaponRange = true;
    this->ConsiderCheckOnNavmesh = true;
}


