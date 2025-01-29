#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "EndBTDecorator_CheckConditionBase.generated.h"

UCLASS(Abstract, Blueprintable)
class UEndBTDecorator_CheckConditionBase : public UBTDecorator {
    GENERATED_BODY()
public:
    UEndBTDecorator_CheckConditionBase();

};

