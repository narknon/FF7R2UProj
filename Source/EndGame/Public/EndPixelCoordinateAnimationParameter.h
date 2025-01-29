#pragma once
#include "CoreMinimal.h"
#include "MaterialParameterExtraPixelCoordinate.h"
#include "EndPixelCoordinateAnimationParameterKey.h"
#include "EndPixelCoordinateAnimationParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndPixelCoordinateAnimationParameter : public FMaterialParameterExtraPixelCoordinate {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndPixelCoordinateAnimationParameterKey> Keys;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMaterialParameterExtraPixelCoordinate EndParameter;
    
    ENDGAME_API FEndPixelCoordinateAnimationParameter();
};

