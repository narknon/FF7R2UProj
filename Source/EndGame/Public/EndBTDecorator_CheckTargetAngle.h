#pragma once
#include "CoreMinimal.h"
#include "EAngleCheckType.h"
#include "EEndAiMathCmp.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckTargetAngle.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckTargetAngle : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EAngleCheckType CheckType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAiMathCmp Operator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CheckTargetAngle;
    
    UEndBTDecorator_CheckTargetAngle();

};

