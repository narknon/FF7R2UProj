#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EndAnimNotifyStateBattleInvincible.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UEndAnimNotifyStateBattleInvincible : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName DamageSourceID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool DamageSourceOnce;
    
    UEndAnimNotifyStateBattleInvincible();

};

