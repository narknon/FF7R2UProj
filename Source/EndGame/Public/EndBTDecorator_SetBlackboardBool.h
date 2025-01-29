#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_SetBlackboardBool.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_SetBlackboardBool : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector BlackboardKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Value;
    
    UEndBTDecorator_SetBlackboardBool();

};

