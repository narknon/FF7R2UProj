#pragma once
#include "CoreMinimal.h"
#include "EndFieldSimpleInteractPluginBase.h"
#include "EndFieldSimpleInteractPluginChangeHubState.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndFieldSimpleInteractPluginChangeHubState : public UEndFieldSimpleInteractPluginBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bToComplete;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bToActive;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bChangeHubStateIsOnlyCompleted;
    
    UEndFieldSimpleInteractPluginChangeHubState();

};

