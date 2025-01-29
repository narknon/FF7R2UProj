#pragma once
#include "CoreMinimal.h"
#include "EndAnimationSettingsAutoDisableLookAt.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimationSettingsAutoDisableLookAt {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverrideHeadBaseAngleThreshold;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DisableAngleThreshold;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DisableAngularVelocityThreshold;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DisableAngularVelocityThresholdApplyAngleOffset;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 InputFrameOffset;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 DuringFrameMin;
    
    ENDGAME_API FEndAnimationSettingsAutoDisableLookAt();
};

