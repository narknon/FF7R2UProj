#pragma once
#include "CoreMinimal.h"
#include "ECommandAbilityInfoType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckCommandAbilityInfo.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckCommandAbilityInfo : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    ECommandAbilityInfoType Type;
    
    UEndBTDecorator_CheckCommandAbilityInfo();

};

