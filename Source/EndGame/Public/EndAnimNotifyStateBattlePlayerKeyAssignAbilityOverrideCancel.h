#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EBattleInputAttackType.h"
#include "EBattleKeyAssignMethodType.h"
#include "EBattleKeyAssignPlaceType.h"
#include "EndAnimNotifyStateBattlePlayerKeyAssignAbilityOverrideCancelCondition.h"
#include "EndAnimNotifyStateBattlePlayerKeyAssignAbilityOverrideCancel.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UEndAnimNotifyStateBattlePlayerKeyAssignAbilityOverrideCancel : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EBattleKeyAssignPlaceType PlaceType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EBattleInputAttackType AttackType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EBattleKeyAssignMethodType MethodType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimNotifyStateBattlePlayerKeyAssignAbilityOverrideCancelCondition Condition;
    
    UEndAnimNotifyStateBattlePlayerKeyAssignAbilityOverrideCancel();

};

