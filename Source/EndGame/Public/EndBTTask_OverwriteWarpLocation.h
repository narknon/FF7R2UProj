#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTTask_OverwriteWarpLocation.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_OverwriteWarpLocation : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector LocationBlackboardKey;
    
    UEndBTTask_OverwriteWarpLocation();

};

