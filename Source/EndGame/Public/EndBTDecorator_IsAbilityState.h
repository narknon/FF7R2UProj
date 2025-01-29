#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsAbilityState.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsAbilityState : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UEndBTDecorator_IsAbilityState();

};

