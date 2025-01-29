#pragma once
#include "CoreMinimal.h"
#include "EAIPCAttackType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_AIPCCheckAttackType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_AIPCCheckAttackType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAIPCAttackType Type;
    
    UEndBTDecorator_AIPCCheckAttackType();

};

