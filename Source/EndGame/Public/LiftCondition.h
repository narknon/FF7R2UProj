#pragma once
#include "CoreMinimal.h"
#include "LiftCondition.generated.h"

USTRUCT(BlueprintType)
struct FLiftCondition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ConditionName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EndConditionName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ConditionValue;
    
    ENDGAME_API FLiftCondition();
};

