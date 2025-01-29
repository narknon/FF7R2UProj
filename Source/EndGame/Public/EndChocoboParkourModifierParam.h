#pragma once
#include "CoreMinimal.h"
#include "EndChocoboParkourModifierParam.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboParkourModifierParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EnableAutoSkipUpStepHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EnableAutoSkipDownStepHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxJumpDistanceXY;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float JumpDistanceXYRate;
    
    ENDGAME_API FEndChocoboParkourModifierParam();
};

