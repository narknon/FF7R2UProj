#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_ApplyAbilityReserveWaitTeleport.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_ApplyAbilityReserveWaitTeleport : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector AbilityHandleIdBBKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector TargetBBKey;
    
    UEndBTDecorator_ApplyAbilityReserveWaitTeleport();

};

