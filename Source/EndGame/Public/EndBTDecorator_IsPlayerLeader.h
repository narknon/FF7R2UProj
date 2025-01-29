#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsPlayerLeader.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsPlayerLeader : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector m_Source;
    
    UEndBTDecorator_IsPlayerLeader();

};

