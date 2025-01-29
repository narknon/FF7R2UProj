#include "EndEnvQueryTest_OverlapMovementBlockCollision.h"

UEndEnvQueryTest_OverlapMovementBlockCollision::UEndEnvQueryTest_OverlapMovementBlockCollision() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->OffsetZ = 25.00f;
}


