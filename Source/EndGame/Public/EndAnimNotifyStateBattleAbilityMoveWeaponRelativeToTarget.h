#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EEndBattleAbilityMoveWeaponRelativeToTargetType.h"
#include "EndAnimNotifyStateBattleAbilityMoveWeaponRelativeToTarget.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class ENDGAME_API UEndAnimNotifyStateBattleAbilityMoveWeaponRelativeToTarget : public UAnimNotifyState {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBattleAbilityMoveWeaponRelativeToTargetType Type;
    
public:
    UEndAnimNotifyStateBattleAbilityMoveWeaponRelativeToTarget();

};

