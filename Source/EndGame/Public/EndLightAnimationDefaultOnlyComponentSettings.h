#pragma once
#include "CoreMinimal.h"
#include "EEndAnimationCurveType.h"
#include "EndLightAnimationParameter.h"
#include "EndLightAnimationDefaultOnlyComponentSettings.generated.h"

class UCurveFloat;

USTRUCT(BlueprintType)
struct FEndLightAnimationDefaultOnlyComponentSettings : public FEndLightAnimationParameter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimationCurveType Curve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UCurveFloat* CurveAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCurveEvaluateInLogarithmicSpace;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Duration;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RandomAdditiveDuration;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RandomOffset;
    
    ENDGAME_API FEndLightAnimationDefaultOnlyComponentSettings();
};

