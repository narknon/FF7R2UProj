#pragma once
#include "CoreMinimal.h"
#include "EEndAnimationCurveType.h"
#include "EndCoordinateAnimationPreviewSettings.generated.h"

USTRUCT(BlueprintType)
struct FEndCoordinateAnimationPreviewSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OverrideId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimationCurveType CurveType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLoop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimelineScale;
    
    ENDGAME_API FEndCoordinateAnimationPreviewSettings();
};

