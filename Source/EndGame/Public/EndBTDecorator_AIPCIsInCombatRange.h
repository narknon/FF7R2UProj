#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_AIPCIsInCombatRange.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_AIPCIsInCombatRange : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector CombatRangeCoefficientBBKey;
    
    UEndBTDecorator_AIPCIsInCombatRange();

};

