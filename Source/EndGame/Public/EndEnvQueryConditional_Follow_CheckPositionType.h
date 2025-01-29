#pragma once
#include "CoreMinimal.h"
#include "EnvQueryConditional.h"
#include "EEndAIFollowPosition.h"
#include "EndEnvQueryConditional_Follow_CheckPositionType.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryConditional_Follow_CheckPositionType : public UEnvQueryConditional {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIFollowPosition> m_PositionTypes;
    
    UEndEnvQueryConditional_Follow_CheckPositionType();

};

