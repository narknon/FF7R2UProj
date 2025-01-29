#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTTask_HinachocoboMagic.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_HinachocoboMagic : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector FromBlackboardKey_InWarp;
    
    UEndBTTask_HinachocoboMagic();

};

