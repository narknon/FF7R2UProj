#include "EndEnvQueryGenerator_ActorsOfType.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

UEndEnvQueryGenerator_ActorsOfType::UEndEnvQueryGenerator_ActorsOfType() {
    this->ItemType = UEnvQueryItemType_Actor::StaticClass();
    this->GeneratorActorType = EEndEnvQueryGeneratorActorType::FollowEscapePoint;
    this->SearchCenter = UEnvQueryContext_Querier::StaticClass();
}


