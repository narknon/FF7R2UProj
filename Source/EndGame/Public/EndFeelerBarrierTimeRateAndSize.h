#pragma once
#include "CoreMinimal.h"
#include "EndFeelerBarrierTimeRateAndSize.generated.h"

USTRUCT(BlueprintType)
struct FEndFeelerBarrierTimeRateAndSize {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeRateSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Size;
    
    ENDGAME_API FEndFeelerBarrierTimeRateAndSize();
};

