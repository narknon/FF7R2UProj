#include "EndEnvQueryGenerator_Cylinder.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

UEndEnvQueryGenerator_Cylinder::UEndEnvQueryGenerator_Cylinder() {
    this->bDefineArc = true;
    this->CircleCenter = UEnvQueryContext_Querier::StaticClass();
}


