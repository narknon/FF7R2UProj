#pragma once
#include "CoreMinimal.h"
#include "EEndAnimationCurveType.h"
#include "EndNormalizedCoordinateAnimationParameter.h"
#include "EndNormalizedCoordinateAnimationMaterial.generated.h"

USTRUCT(BlueprintType)
struct FEndNormalizedCoordinateAnimationMaterial {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MaterialNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MeshNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndNormalizedCoordinateAnimationParameter Default;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndNormalizedCoordinateAnimationParameter> Override;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimationCurveType DefaultCurve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DefaultDuration;
    
    ENDGAME_API FEndNormalizedCoordinateAnimationMaterial();
};

