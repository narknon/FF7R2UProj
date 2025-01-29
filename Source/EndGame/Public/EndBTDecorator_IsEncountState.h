#pragma once
#include "CoreMinimal.h"
#include "EEndEncountStateType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsEncountState.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsEncountState : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndEncountStateType> States;
    
    UEndBTDecorator_IsEncountState();

};

