#pragma once
#include "CoreMinimal.h"
#include "EndRestrictedAreaNotifyData.generated.h"

USTRUCT(BlueprintType)
struct FEndRestrictedAreaNotifyData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TriggerName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Interval;
    
    ENDGAME_API FEndRestrictedAreaNotifyData();
};

