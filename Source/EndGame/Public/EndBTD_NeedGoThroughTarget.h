#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTD_NeedGoThroughTarget.generated.h"

UCLASS(Blueprintable)
class UEndBTD_NeedGoThroughTarget : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector FromBlackboardKey_Target;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector FromBlackboardKey_MoveTo;
    
    UEndBTD_NeedGoThroughTarget();

};

