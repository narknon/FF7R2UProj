#include "EndEnvQueryConditional_Distance.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

UEndEnvQueryConditional_Distance::UEndEnvQueryConditional_Distance() {
    this->DistanceFrom = UEnvQueryContext_Querier::StaticClass();
    this->DistanceTo = UEnvQueryContext_Querier::StaticClass();
    this->Operator = EEndAiMathCmp::Equal;
    this->DistanceType = EEndAIDistanceType::Dist2D;
    this->bUseBodyRadius_From = false;
    this->bUseBodyRadius_To = false;
}


