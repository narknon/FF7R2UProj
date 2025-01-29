#pragma once
#include "CoreMinimal.h"
#include "EndJenovaPulseWallPulseContext.generated.h"

USTRUCT(BlueprintType)
struct FEndJenovaPulseWallPulseContext {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PulseTimer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PulsePlayRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PulseWaitTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PulseScale;
    
    ENDGAME_API FEndJenovaPulseWallPulseContext();
};

