#pragma once
#include "CoreMinimal.h"
#include "EndFieldSimpleInteractPluginBase.h"
#include "EndFieldSimpleInteractPluginSendTrigger.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndFieldSimpleInteractPluginSendTrigger : public UEndFieldSimpleInteractPluginBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TriggerName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisalbeTriggerNameMatching;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSendTriggerIsOnlyCompleted;
    
    UEndFieldSimpleInteractPluginSendTrigger();

};

