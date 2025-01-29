#pragma once
#include "CoreMinimal.h"
#include "EndTinyBroncoDolphinActionLotteryData.generated.h"

USTRUCT(BlueprintType)
struct FEndTinyBroncoDolphinActionLotteryData {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 SelectWeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActionDefinitionName;
    
    ENDGAME_API FEndTinyBroncoDolphinActionLotteryData();
};

