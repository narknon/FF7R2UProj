#pragma once
#include "CoreMinimal.h"
#include "EndBikeAIHelicopterMoveParam_MoveForward.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeAIHelicopterMoveParam_MoveForward {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RelativeSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RelativeSpeedOnRotateYaw;
    
    ENDGAME_API FEndBikeAIHelicopterMoveParam_MoveForward();
};

