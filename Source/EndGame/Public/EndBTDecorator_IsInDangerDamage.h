#pragma once
#include "CoreMinimal.h"
#include "EEndAIDangerSensorType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsInDangerDamage.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsInDangerDamage : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIDangerSensorType Type;
    
    UEndBTDecorator_IsInDangerDamage();

};

