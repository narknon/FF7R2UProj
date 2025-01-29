#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "endBTTask_AIPCUseAbility.generated.h"

UCLASS(Blueprintable)
class UendBTTask_AIPCUseAbility : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseCharacterRotation;
    
    UendBTTask_AIPCUseAbility();

};

