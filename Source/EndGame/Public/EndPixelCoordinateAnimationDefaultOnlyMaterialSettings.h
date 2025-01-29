#pragma once
#include "CoreMinimal.h"
#include "EEndAnimationCurveType.h"
#include "EndPixelCoordinateAnimationParameter.h"
#include "EndPixelCoordinateAnimationDefaultOnlyMaterialSettings.generated.h"

USTRUCT(BlueprintType)
struct FEndPixelCoordinateAnimationDefaultOnlyMaterialSettings : public FEndPixelCoordinateAnimationParameter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MaterialNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MeshNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimationCurveType Curve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Duration;
    
    ENDGAME_API FEndPixelCoordinateAnimationDefaultOnlyMaterialSettings();
};

