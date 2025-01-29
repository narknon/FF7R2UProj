#pragma once
#include "CoreMinimal.h"
#include "End3DAudioTriggerRequest.generated.h"

USTRUCT(BlueprintType)
struct FEnd3DAudioTriggerRequest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StateTrigger;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimePercent;
    
    ENDGAME_API FEnd3DAudioTriggerRequest();
};

