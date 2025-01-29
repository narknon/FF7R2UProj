#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyStateBattleDamagePartyChocoboCondition.h"
#include "EndAnimNotifyStateBattleDamage.h"
#include "EndAnimNotifyStateBattleDamagePartyChocobo.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class ENDGAME_API UEndAnimNotifyStateBattleDamagePartyChocobo : public UEndAnimNotifyStateBattleDamage {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimNotifyStateBattleDamagePartyChocoboCondition CreateCondition;
    
    UEndAnimNotifyStateBattleDamagePartyChocobo();

};

