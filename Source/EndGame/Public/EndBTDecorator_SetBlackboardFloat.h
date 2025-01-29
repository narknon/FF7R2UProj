#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_SetBlackboardFloat.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_SetBlackboardFloat : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector BlackboardKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Value;
    
    UEndBTDecorator_SetBlackboardFloat();

};

