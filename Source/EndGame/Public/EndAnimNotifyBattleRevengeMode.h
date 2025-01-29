#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyBattleRevengeMode.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyBattleRevengeMode : public UAnimNotify {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Time;
    
public:
    UEndAnimNotifyBattleRevengeMode();

};

