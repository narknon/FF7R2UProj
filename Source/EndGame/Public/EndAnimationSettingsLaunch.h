#pragma once
#include "CoreMinimal.h"
#include "EndAnimationSettingsLaunch.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimationSettingsLaunch {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LandAnimTimer;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WakeUpMinTime;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WakeUpCrashLandingIKTime;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LaunchPowerReduction;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LaunchRagdollAsLandingTime;
    
    ENDGAME_API FEndAnimationSettingsLaunch();
};

