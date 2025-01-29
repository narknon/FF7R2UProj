#pragma once
#include "CoreMinimal.h"
#include "EnvQueryConditional.h"
#include "EEndAIMoveDefWarpToNearTheTargetType.h"
#include "EndEnvQueryConditional_Enemy_WarpToNearTheTargetType.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryConditional_Enemy_WarpToNearTheTargetType : public UEnvQueryConditional {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIMoveDefWarpToNearTheTargetType WarpType;
    
    UEndEnvQueryConditional_Enemy_WarpToNearTheTargetType();

};

