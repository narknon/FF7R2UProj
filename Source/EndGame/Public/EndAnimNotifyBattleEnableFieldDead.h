#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyBattleEnableFieldDead.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyBattleEnableFieldDead : public UAnimNotify {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Enable;
    
public:
    UEndAnimNotifyBattleEnableFieldDead();

};

