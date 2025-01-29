#pragma once
#include "CoreMinimal.h"
#include "EndBikeAIHelicopterAbilitySet.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeAIHelicopterAbilitySet {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilitySet_FR;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilitySet_FL;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilitySet_RR;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilitySet_RL;
    
    ENDGAME_API FEndBikeAIHelicopterAbilitySet();
};

