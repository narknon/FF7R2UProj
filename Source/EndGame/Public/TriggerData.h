#pragma once
#include "CoreMinimal.h"
#include "EAnimalTriggerCondition.h"
#include "TriggerData.generated.h"

USTRUCT(BlueprintType)
struct FTriggerData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAnimalTriggerCondition TriggerCondition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 TriggerValue;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TriggerName;
    
    ENDGAME_API FTriggerData();
};

