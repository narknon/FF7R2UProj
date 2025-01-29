#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTTask_SetSequencerPvEscapeLocation.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_SetSequencerPvEscapeLocation : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector LocationBlackboardKey;
    
    UEndBTTask_SetSequencerPvEscapeLocation();

};

