#pragma once
#include "CoreMinimal.h"
#include "EEndAiMathCmp.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CompareTargetPropertyDefense.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CompareTargetPropertyDefense : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAiMathCmp Operator;
    
    UEndBTDecorator_CompareTargetPropertyDefense();

};

