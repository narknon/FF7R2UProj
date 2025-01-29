#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndBattleAbilityCancelComboCondition.h"
#include "EndAnimNotifyBattleSetNormalAttackOverrideCount.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyBattleSetNormalAttackOverrideCount : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 Count;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EndBattleAbilityCancelComboCondition Condition;
    
    UEndAnimNotifyBattleSetNormalAttackOverrideCount();

};

