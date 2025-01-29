#pragma once
#include "CoreMinimal.h"
#include "EndLocomotionRevaluationSetting.h"
#include "EndLocomotionStrafingRevaluationSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndLocomotionStrafingRevaluationSetting : public FEndLocomotionRevaluationSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableDirectChangeDirection;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverrideNeutral;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableDirectChangeDirectionForNeutral;
    
    ENDGAME_API FEndLocomotionStrafingRevaluationSetting();
};

