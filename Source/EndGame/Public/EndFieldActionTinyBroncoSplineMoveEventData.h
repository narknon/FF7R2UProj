#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionTinyBroncoSplineMoveEventData.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldActionTinyBroncoSplineMoveEventData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InputKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TriggerName;
    
    ENDGAME_API FEndFieldActionTinyBroncoSplineMoveEventData();
};

