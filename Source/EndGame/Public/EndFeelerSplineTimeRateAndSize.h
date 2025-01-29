#pragma once
#include "CoreMinimal.h"
#include "EndFeelerSplineTimeRateAndSize.generated.h"

USTRUCT(BlueprintType)
struct FEndFeelerSplineTimeRateAndSize {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeRateSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Size;
    
    ENDGAME_API FEndFeelerSplineTimeRateAndSize();
};

