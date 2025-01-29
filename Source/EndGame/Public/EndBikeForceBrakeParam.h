#pragma once
#include "CoreMinimal.h"
#include "EndBikeForceBrakeParam.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeForceBrakeParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BrakePower;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BrakeTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinSpeed;
    
    ENDGAME_API FEndBikeForceBrakeParam();
};

