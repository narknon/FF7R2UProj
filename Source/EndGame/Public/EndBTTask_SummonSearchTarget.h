#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EndBTTask_SummonSearchTarget.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_SummonSearchTarget : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bBossFirst;
    
    UEndBTTask_SummonSearchTarget();

};

