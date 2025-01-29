#pragma once
#include "CoreMinimal.h"
#include "EEndAIInterestActionCommand.h"
#include "EndAIInterestActionInfo.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestActionInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName commandID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIInterestActionCommand Command;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName PollingID;
    
    FEndAIInterestActionInfo();
};

