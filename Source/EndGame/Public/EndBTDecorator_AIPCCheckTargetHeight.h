#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EEndAiMathCmp.h"
#include "ETargetType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_AIPCCheckTargetHeight.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_AIPCCheckTargetHeight : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    ETargetType TargetType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAiMathCmp Operator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Height;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector HeightBBKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseBBKey;
    
    UEndBTDecorator_AIPCCheckTargetHeight();

};

