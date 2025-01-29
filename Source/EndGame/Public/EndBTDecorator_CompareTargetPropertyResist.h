#pragma once
#include "CoreMinimal.h"
#include "EAIPCDamagePropertyFlag.h"
#include "EEndAiMathCmp.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CompareTargetPropertyResist.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CompareTargetPropertyResist : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAiMathCmp Operator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAIPCDamagePropertyFlag PropertyTypeA;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAIPCDamagePropertyFlag PropertyTypeB;
    
    UEndBTDecorator_CompareTargetPropertyResist();

};

