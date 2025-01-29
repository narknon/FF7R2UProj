#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EEndLocomotionState.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsLocomotionState.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsLocomotionState : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector m_Source;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndLocomotionState> m_LocomotionStates;
    
    UEndBTDecorator_IsLocomotionState();

};

