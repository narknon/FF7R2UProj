#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTD_SummonSetConfrontDistanceForEnd1.generated.h"

UCLASS(Blueprintable)
class UEndBTD_SummonSetConfrontDistanceForEnd1 : public UBTDecorator {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector FromBlackboardKey_Base;
    
    UEndBTD_SummonSetConfrontDistanceForEnd1();

};

