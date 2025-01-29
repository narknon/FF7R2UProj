#pragma once
#include "CoreMinimal.h"
#include "EEndDeformAnimationType.h"
#include "EndDeformAnimationPreviewSettings.generated.h"

USTRUCT(BlueprintType)
struct FEndDeformAnimationPreviewSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndDeformAnimationType AnimationType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartFrame;
    
    ENDGAME_API FEndDeformAnimationPreviewSettings();
};

