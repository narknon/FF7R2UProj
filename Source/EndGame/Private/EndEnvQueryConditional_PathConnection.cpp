#include "EndEnvQueryConditional_PathConnection.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

UEndEnvQueryConditional_PathConnection::UEndEnvQueryConditional_PathConnection() {
    this->From = UEnvQueryContext_Querier::StaticClass();
    this->To = UEnvQueryContext_Querier::StaticClass();
    this->QueryFilterType = EEndQueryFilterType::Default;
    this->bItemProjection = true;
}


