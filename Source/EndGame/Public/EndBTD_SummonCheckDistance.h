#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EEndAiMathCmp.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTD_SummonCheckDistance.generated.h"

UCLASS(Blueprintable)
class UEndBTD_SummonCheckDistance : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector ToBlackboardKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAiMathCmp Operator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector CheckDistanceBlackboardKey;
    
    UEndBTD_SummonCheckDistance();

};

