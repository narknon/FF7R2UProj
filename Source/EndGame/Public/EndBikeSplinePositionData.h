#pragma once
#include "CoreMinimal.h"
#include "EndBikeSplinePositionData.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeSplinePositionData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 SplineIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 LapCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InputKey;
    
    ENDGAME_API FEndBikeSplinePositionData();
};

