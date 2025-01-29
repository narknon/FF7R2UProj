#pragma once
#include "CoreMinimal.h"
#include "MaterialParameterExtraPixelCoordinate.h"
#include "EndPixelCoordinateAnimationParameterKey.generated.h"

USTRUCT(BlueprintType)
struct FEndPixelCoordinateAnimationParameterKey {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Time;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bConstant;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMaterialParameterExtraPixelCoordinate Parameter;
    
    ENDGAME_API FEndPixelCoordinateAnimationParameterKey();
};

