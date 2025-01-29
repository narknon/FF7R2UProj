#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyBattleSelfBuffLevelUp.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyBattleSelfBuffLevelUp : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Upgrade;
    
    UEndAnimNotifyBattleSelfBuffLevelUp();

};

