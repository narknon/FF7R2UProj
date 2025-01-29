#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyStateBattlePlayerKeyAssignAbilityOverrideCancelConditionType.h"
#include "EndAnimNotifyStateBattlePlayerKeyAssignAbilityOverrideCancelCondition.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimNotifyStateBattlePlayerKeyAssignAbilityOverrideCancelCondition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimNotifyStateBattlePlayerKeyAssignAbilityOverrideCancelConditionType ConditionType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ParameterName;
    
    ENDGAME_API FEndAnimNotifyStateBattlePlayerKeyAssignAbilityOverrideCancelCondition();
};

