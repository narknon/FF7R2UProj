#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAttributeResistType.h"
#include "EEndAiMathCmp.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckTargetAttributeBuffResist.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckTargetAttributeBuffResist : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAiMathCmp Operator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBattleAttributeResistType ResistType;
    
    UEndBTDecorator_CheckTargetAttributeBuffResist();

};

