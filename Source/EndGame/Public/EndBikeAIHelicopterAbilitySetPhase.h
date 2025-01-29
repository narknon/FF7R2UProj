#pragma once
#include "CoreMinimal.h"
#include "EndBikeAIHelicopterAbilitySet.h"
#include "EndBikeSplinePositionData.h"
#include "EndBikeAIHelicopterAbilitySetPhase.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeAIHelicopterAbilitySetPhase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBikeSplinePositionData SplinePosition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBikeAIHelicopterAbilitySet AbilitySet;
    
    ENDGAME_API FEndBikeAIHelicopterAbilitySetPhase();
};

