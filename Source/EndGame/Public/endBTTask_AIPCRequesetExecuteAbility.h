#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "endBTTask_AIPCRequesetExecuteAbility.generated.h"

UCLASS(Blueprintable)
class UendBTTask_AIPCRequesetExecuteAbility : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeOut;
    
    UendBTTask_AIPCRequesetExecuteAbility();

};

