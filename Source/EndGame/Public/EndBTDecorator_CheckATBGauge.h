#pragma once
#include "CoreMinimal.h"
#include "EEndAiMathCmp.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckATBGauge.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckATBGauge : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAiMathCmp Operator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Gauge;
    
    UEndBTDecorator_CheckATBGauge();

};

