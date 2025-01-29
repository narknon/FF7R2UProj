#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CanCancelTurn.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CanCancelTurn : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UEndBTDecorator_CanCancelTurn();

};

