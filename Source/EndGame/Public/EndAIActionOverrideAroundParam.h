#pragma once
#include "CoreMinimal.h"
#include "EndAIActionOverrideAroundParam.generated.h"

USTRUCT(BlueprintType)
struct FEndAIActionOverrideAroundParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MoveDefTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AroundTimeOut;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AroundDistance;
    
    ENDGAME_API FEndAIActionOverrideAroundParam();
};

