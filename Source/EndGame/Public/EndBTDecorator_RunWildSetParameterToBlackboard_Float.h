#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EEndAnimalRunFloatParameterType.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_RunWildSetParameterToBlackboard_Float.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_RunWildSetParameterToBlackboard_Float : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimalRunFloatParameterType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector BlackboardKey;
    
    UEndBTDecorator_RunWildSetParameterToBlackboard_Float();

};

