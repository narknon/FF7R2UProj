#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndLocomotionRevaluationSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndLocomotionRevaluationSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RevaluationTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> PoseMatchingTimings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVector2D> AllowedCurrentTimeRatioRanges;
    
    ENDGAME_API FEndLocomotionRevaluationSetting();
};

