#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifySendStateTrigger.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifySendStateTrigger : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString StateTriggerName;
    
    UEndAnimNotifySendStateTrigger();

};

