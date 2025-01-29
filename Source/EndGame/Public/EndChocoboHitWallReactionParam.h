#pragma once
#include "CoreMinimal.h"
#include "EndChocoboHitWallReactionParam.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboHitWallReactionParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableHitReaction;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PlayMotionLimitDeltaSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PlayMotionLimitDeltaAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PlayMotionLimitDeltaTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PlayMotionLimitDeltaSpeedOnCloseToWall;
    
    ENDGAME_API FEndChocoboHitWallReactionParam();
};

