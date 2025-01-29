#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAnimationCurveType.h"
#include "AnimNotify_EndCoordinateAnimation.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UAnimNotify_EndCoordinateAnimation : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CoordinateAnimationSettingsId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimationCurveType Curve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLoop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Duration;
    
    UAnimNotify_EndCoordinateAnimation();

};

