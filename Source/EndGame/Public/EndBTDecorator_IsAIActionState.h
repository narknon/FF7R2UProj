#pragma once
#include "CoreMinimal.h"
#include "EEndAIActionState.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsAIActionState.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsAIActionState : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIActionState> States;
    
    UEndBTDecorator_IsAIActionState();

};

