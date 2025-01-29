#pragma once
#include "CoreMinimal.h"
#include "MaterialParameterExtraNormalizedCoordinate.h"
#include "EndNormalizedCoordinateAnimationParameterKey.h"
#include "EndNormalizedCoordinateAnimationParameter.generated.h"

class UMaterialInterface;

USTRUCT(BlueprintType)
struct FEndNormalizedCoordinateAnimationParameter : public FMaterialParameterExtraNormalizedCoordinate {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNormalizedCoordinateAnimationParameterKey> Keys;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMaterialParameterExtraNormalizedCoordinate EndParameter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, UMaterialInterface*> OverrideMaterials;
    
    ENDGAME_API FEndNormalizedCoordinateAnimationParameter();
};

