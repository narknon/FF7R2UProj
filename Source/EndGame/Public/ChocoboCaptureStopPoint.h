#pragma once
#include "CoreMinimal.h"
#include "ChocoboCaptureStopPoint.generated.h"

USTRUCT(BlueprintType)
struct FChocoboCaptureStopPoint {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 _StopIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 _StopCount;
    
    ENDGAME_API FChocoboCaptureStopPoint();
};

