#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_DurationBase.h"
#include "EndBTDecorator_SetForceAvoidance.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_SetForceAvoidance : public UEndBTDecorator_DurationBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector TargetBBKey;
    
    UEndBTDecorator_SetForceAvoidance();

};

