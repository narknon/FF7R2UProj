#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsValidAbilityHandle.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsValidAbilityHandle : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector HandleIdBlackboardKey;
    
    UEndBTDecorator_IsValidAbilityHandle();

};

