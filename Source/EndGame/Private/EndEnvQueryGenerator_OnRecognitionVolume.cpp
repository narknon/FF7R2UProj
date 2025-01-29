#include "EndEnvQueryGenerator_OnRecognitionVolume.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

UEndEnvQueryGenerator_OnRecognitionVolume::UEndEnvQueryGenerator_OnRecognitionVolume() {
    this->GenerateAround = UEnvQueryContext_Querier::StaticClass();
}


