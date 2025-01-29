#pragma once
#include "CoreMinimal.h"
#include "EnvQueryConditional.h"
#include "EEndEnvQueryAIPCPathConnectionTargetType.h"
#include "EEndQueryFilterType.h"
#include "EndEnvQueryConditional_IsPathConnectionToTarget.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryConditional_IsPathConnectionToTarget : public UEnvQueryConditional {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndEnvQueryAIPCPathConnectionTargetType TargetType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndQueryFilterType QueryFilterType;
    
    UEndEnvQueryConditional_IsPathConnectionToTarget();

};

