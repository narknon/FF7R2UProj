#pragma once
#include "CoreMinimal.h"
#include "EEndAnimationCurveType.h"
#include "EndNormalizedCoordinateAnimationParameter.h"
#include "EndNormalizedCoordinateAnimationDefaultOnlyMaterialSettings.generated.h"

USTRUCT(BlueprintType)
struct FEndNormalizedCoordinateAnimationDefaultOnlyMaterialSettings : public FEndNormalizedCoordinateAnimationParameter {
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
    
    ENDGAME_API FEndNormalizedCoordinateAnimationDefaultOnlyMaterialSettings();
};

