#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyBattleTensionGaugeAdd.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyBattleTensionGaugeAdd : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Value;
    
    UEndAnimNotifyBattleTensionGaugeAdd();

};

