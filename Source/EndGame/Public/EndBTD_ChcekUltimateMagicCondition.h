#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTD_ChcekUltimateMagicCondition.generated.h"

UCLASS(Blueprintable)
class UEndBTD_ChcekUltimateMagicCondition : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector FromBlackboardKey_AbilityExecuteState;
    
    UEndBTD_ChcekUltimateMagicCondition();

};

