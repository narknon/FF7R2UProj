#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_SetCautionMoveWaitTime.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_SetCautionMoveWaitTime : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector BlackboardKey;
    
    UEndBTDecorator_SetCautionMoveWaitTime();

};

