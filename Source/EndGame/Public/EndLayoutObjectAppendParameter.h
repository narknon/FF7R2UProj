#pragma once
#include "CoreMinimal.h"
#include "EndChadleyPointParameters.h"
#include "EndTargetPointParameters.h"
#include "EndTreasurePointParameters.h"
#include "EndWorldItemParameters.h"
#include "EndLayoutObjectAppendParameter.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndLayoutObjectAppendParameter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndTargetPointParameters> EndTargetPointParamArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndWorldItemParameters> WorldItemParamArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndTreasurePointParameters> TreasureParamArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndChadleyPointParameters> ChadleyParamArray;
    
    FEndLayoutObjectAppendParameter();
};

