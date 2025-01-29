#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyBattleAbilityAnimationReplaceCondition.h"
#include "EndAnimNotifyBattleAbilityAnimationReplaceParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimNotifyBattleAbilityAnimationReplaceParameter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString ReplaceName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimNotifyBattleAbilityAnimationReplaceCondition Condition;
    
    ENDGAME_API FEndAnimNotifyBattleAbilityAnimationReplaceParameter();
};

