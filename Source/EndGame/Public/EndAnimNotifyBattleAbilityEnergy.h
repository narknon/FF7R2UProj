#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAnimNotifyBattleAbilityEnergyType.h"
#include "EndAnimNotifyBattleAbilityEnergy.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyBattleAbilityEnergy : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimNotifyBattleAbilityEnergyType Type;
    
    UEndAnimNotifyBattleAbilityEnergy();

};

