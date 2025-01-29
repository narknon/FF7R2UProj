#pragma once
#include "CoreMinimal.h"
#include "DataProviders/AIDataProvider.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "EndEnvQueryGenerator_AIPCOnTerrainSensor.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndEnvQueryGenerator_AIPCOnTerrainSensor : public UEnvQueryGenerator_ProjectedPoints {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FAIDataProviderFloatValue SpaceBetween;
    
    UEndEnvQueryGenerator_AIPCOnTerrainSensor();

};

