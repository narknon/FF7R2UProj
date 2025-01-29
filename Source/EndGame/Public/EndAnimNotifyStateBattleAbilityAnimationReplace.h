#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EndAnimNotifyBattleAbilityAnimationReplaceParameter.h"
#include "EndAnimNotifyStateBattleAbilityAnimationReplace.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UEndAnimNotifyStateBattleAbilityAnimationReplace : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAnimNotifyBattleAbilityAnimationReplaceParameter> Parameters;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString ReplaceName;
    
    UEndAnimNotifyStateBattleAbilityAnimationReplace();

};

