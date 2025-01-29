#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EndBTTask_AIPCAttackBase.generated.h"

UCLASS(Abstract, Blueprintable)
class UEndBTTask_AIPCAttackBase : public UBTTaskNode {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSkipApproachPhase;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSupportCombinationAttack;
    
public:
    UEndBTTask_AIPCAttackBase();

};

