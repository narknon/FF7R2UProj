#pragma once
#include "CoreMinimal.h"
#include "EndInputVelocitySetting.generated.h"

USTRUCT(BlueprintType)
struct FEndInputVelocitySetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableVelocityInput;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InputVelocityMax;
    
    ENDGAME_API FEndInputVelocitySetting();
};

