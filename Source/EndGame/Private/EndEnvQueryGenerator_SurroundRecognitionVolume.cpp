#include "EndEnvQueryGenerator_SurroundRecognitionVolume.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

UEndEnvQueryGenerator_SurroundRecognitionVolume::UEndEnvQueryGenerator_SurroundRecognitionVolume() {
    this->GenerateAround = UEnvQueryContext_Querier::StaticClass();
}


