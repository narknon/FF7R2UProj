#pragma once
#include "CoreMinimal.h"
#include "EEndAIState.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsAIState.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsAIState : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIState> AIStates;
    
    UEndBTDecorator_IsAIState();

};

