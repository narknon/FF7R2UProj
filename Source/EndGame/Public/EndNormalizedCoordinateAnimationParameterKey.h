#pragma once
#include "CoreMinimal.h"
#include "MaterialParameterExtraNormalizedCoordinate.h"
#include "EndNormalizedCoordinateAnimationParameterKey.generated.h"

USTRUCT(BlueprintType)
struct FEndNormalizedCoordinateAnimationParameterKey {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Time;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bConstant;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMaterialParameterExtraNormalizedCoordinate Parameter;
    
    ENDGAME_API FEndNormalizedCoordinateAnimationParameterKey();
};

