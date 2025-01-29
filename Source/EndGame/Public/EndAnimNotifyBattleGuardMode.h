#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyBattleGuardMode.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyBattleGuardMode : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Flag;
    
    UEndAnimNotifyBattleGuardMode();

};

