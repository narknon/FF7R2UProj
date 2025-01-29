#pragma once
#include "CoreMinimal.h"
#include "EEndAIFollowBehaviorTreeFlow.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_SetFollowBehaviorTreeFlow.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_SetFollowBehaviorTreeFlow : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIFollowBehaviorTreeFlow Flow;
    
    UEndBTDecorator_SetFollowBehaviorTreeFlow();

};

