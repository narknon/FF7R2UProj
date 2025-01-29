#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "ESummonBattleBehavior.h"
#include "EndBTD_SummonSetBattleBehavior.generated.h"

UCLASS(Blueprintable)
class UEndBTD_SummonSetBattleBehavior : public UBTDecorator {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector ToBlackboardKey_BattleBehavior;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ESummonBattleBehavior NewBattleBehavior;
    
    UEndBTD_SummonSetBattleBehavior();

};

