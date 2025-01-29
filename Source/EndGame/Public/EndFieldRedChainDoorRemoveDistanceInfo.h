#pragma once
#include "CoreMinimal.h"
#include "EndFieldRedChainDoorRemoveDistanceInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldRedChainDoorRemoveDistanceInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TargetRemoveDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RemovedTriggerName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AfterRemovedDropTriggerName;
    
    ENDGAME_API FEndFieldRedChainDoorRemoveDistanceInfo();
};

