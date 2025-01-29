#pragma once
#include "CoreMinimal.h"
#include "EnvQueryConditional.h"
#include "EEndQueryFilterType.h"
#include "Templates/SubclassOf.h"
#include "EndEnvQueryConditional_PathConnection.generated.h"

class UEnvQueryContext;

UCLASS(Blueprintable)
class UEndEnvQueryConditional_PathConnection : public UEnvQueryConditional {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEnvQueryContext> From;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEnvQueryContext> To;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndQueryFilterType QueryFilterType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bItemProjection;
    
    UEndEnvQueryConditional_PathConnection();

};

