#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndBattleEnvironmentResetConditionNotify.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndBattleEnvironmentResetConditionNotify : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool HP;
    
    UEndBattleEnvironmentResetConditionNotify();

};

