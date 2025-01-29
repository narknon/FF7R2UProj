#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyBattleDamageRandomProbabilityEffect.h"
#include "EndAnimNotifyBattleDamageRandomParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimNotifyBattleDamageRandomParameter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 Probability;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimNotifyBattleDamageRandomProbabilityEffect ProbabilityEffect;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> DamageSourceIDs;
    
    ENDGAME_API FEndAnimNotifyBattleDamageRandomParameter();
};

