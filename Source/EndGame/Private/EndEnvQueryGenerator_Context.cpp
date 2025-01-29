#include "EndEnvQueryGenerator_Context.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"

UEndEnvQueryGenerator_Context::UEndEnvQueryGenerator_Context() {
    this->Context = UEnvQueryContext_Querier::StaticClass();
    this->ContextItemType = UEnvQueryItemType_Point::StaticClass();
}


