#pragma once
#include "CoreMinimal.h"
#include "EAnimalRefereeType.h"
#include "AnimalRefereeCondition.generated.h"

USTRUCT(BlueprintType)
struct FAnimalRefereeCondition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ConditionName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAnimalRefereeType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ConditionValue;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SucceedStateTrigger;
    
    ENDGAME_API FAnimalRefereeCondition();
};

