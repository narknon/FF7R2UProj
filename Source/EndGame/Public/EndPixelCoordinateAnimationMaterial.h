#pragma once
#include "CoreMinimal.h"
#include "EEndAnimationCurveType.h"
#include "EndPixelCoordinateAnimationParameter.h"
#include "EndPixelCoordinateAnimationMaterial.generated.h"

USTRUCT(BlueprintType)
struct FEndPixelCoordinateAnimationMaterial {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MaterialNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MeshNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndPixelCoordinateAnimationParameter Default;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndPixelCoordinateAnimationParameter> Override;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimationCurveType DefaultCurve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DefaultDuration;
    
    ENDGAME_API FEndPixelCoordinateAnimationMaterial();
};

