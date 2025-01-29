#pragma once
#include "CoreMinimal.h"
#include "EndFeelerFollowingTimeRateAndSize.generated.h"

USTRUCT(BlueprintType)
struct FEndFeelerFollowingTimeRateAndSize {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeRateSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Size;
    
    ENDGAME_API FEndFeelerFollowingTimeRateAndSize();
};

