#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndTinyBroncoDolphinActionLotteryData.h"
#include "EndTinyBroncoDolphinActionLotteryListPerSpeed.generated.h"

USTRUCT(BlueprintType)
struct FEndTinyBroncoDolphinActionLotteryListPerSpeed {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval SpeedRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndTinyBroncoDolphinActionLotteryData> LotteryList;
    
    ENDGAME_API FEndTinyBroncoDolphinActionLotteryListPerSpeed();
};

