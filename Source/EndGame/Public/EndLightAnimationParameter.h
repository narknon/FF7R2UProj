#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndLightAnimationParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndLightAnimationParameter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Intensity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FColor LightColor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    float Temperature;
    
    ENDGAME_API FEndLightAnimationParameter();
};

