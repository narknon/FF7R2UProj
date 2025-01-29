#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAnimNotifyBattleUniqueAbilityChargeCrystalActionType.h"
#include "EndAnimNotifyBattleUniqueAbilityChargeCrystal.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyBattleUniqueAbilityChargeCrystal : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimNotifyBattleUniqueAbilityChargeCrystalActionType ActionType;
    
    UEndAnimNotifyBattleUniqueAbilityChargeCrystal();

};

