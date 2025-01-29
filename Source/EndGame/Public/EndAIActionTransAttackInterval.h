#pragma once
#include "CoreMinimal.h"
#include "EEndAIIntervalType.h"
#include "EndAIActionTransAttackInterval.generated.h"

USTRUCT(BlueprintType)
struct FEndAIActionTransAttackInterval {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIIntervalType IntervalType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDefault;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Interval;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float IntervalWidth;
    
    ENDGAME_API FEndAIActionTransAttackInterval();
};

