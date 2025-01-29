#pragma once
#include "CoreMinimal.h"
#include "DataProviders/AIDataProvider.h"
#include "DataProviders/AIDataProvider.h"
#include "EnvironmentQuery/EnvQueryGenerator.h"
#include "EEndEnvQueryGeneratorActorType.h"
#include "Templates/SubclassOf.h"
#include "EndEnvQueryGenerator_ActorsOfType.generated.h"

class UEnvQueryContext;

UCLASS(Blueprintable, EditInlineNew)
class UEndEnvQueryGenerator_ActorsOfType : public UEnvQueryGenerator {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndEnvQueryGeneratorActorType GeneratorActorType;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FAIDataProviderBoolValue GenerateOnlyActorsInRadius;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FAIDataProviderFloatValue SearchRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEnvQueryContext> SearchCenter;
    
    UEndEnvQueryGenerator_ActorsOfType();

};

