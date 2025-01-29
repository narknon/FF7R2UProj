#pragma once
#include "CoreMinimal.h"
#include "EndAnimationSettingsFall.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimationSettingsFall {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DashLandingBlendInTime;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DashLandingBlendOutTime;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DashLandingRootMotionScale;
    
    ENDGAME_API FEndAnimationSettingsFall();
};

