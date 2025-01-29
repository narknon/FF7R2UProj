#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_ClearBlackboard.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_ClearBlackboard : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector BlackboardKey;
    
    UEndBTDecorator_ClearBlackboard();

};

