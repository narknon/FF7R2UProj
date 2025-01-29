#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EEndAnimBehaviorMode.h"
#include "EEndLocomotionState.h"
#include "EndLocomotionBlendSpacePlayerRotationRate.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndLocomotionBlendSpacePlayerRotationRate {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimBehaviorMode BehaviorMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndLocomotionState LocomotionState;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotationRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D ApplyTimeRatioRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ApplyAnimationSet;
    
    FEndLocomotionBlendSpacePlayerRotationRate();
};

