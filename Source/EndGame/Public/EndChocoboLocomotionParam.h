#pragma once
#include "CoreMinimal.h"
#include "EndChocoboLocomotionParam.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboLocomotionParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RootMotionTranslationScale;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RootMotionTranslationScaleMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TargetSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TargetSpeedInSwim;
    
    ENDGAME_API FEndChocoboLocomotionParam();
};

