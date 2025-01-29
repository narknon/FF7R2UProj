#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckFatMoogleGaugeLevel.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckFatMoogleGaugeLevel : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Level;
    
    UEndBTDecorator_CheckFatMoogleGaugeLevel();

};

