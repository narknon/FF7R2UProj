#pragma once
#include "CoreMinimal.h"
#include "EAIPCDamagePropertyFlag.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckTargetPropertyResist.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckTargetPropertyResist : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAIPCDamagePropertyFlag PropertyType;
    
    UEndBTDecorator_CheckTargetPropertyResist();

};

