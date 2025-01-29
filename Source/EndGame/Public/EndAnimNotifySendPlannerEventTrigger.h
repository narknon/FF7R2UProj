#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifySendPlannerEventTrigger.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifySendPlannerEventTrigger : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString TriggerID;
    
    UEndAnimNotifySendPlannerEventTrigger();

};

