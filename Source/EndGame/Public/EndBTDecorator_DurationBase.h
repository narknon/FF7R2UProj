#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "EndBTDecorator_DurationBase.generated.h"

UCLASS(Abstract, Blueprintable)
class UEndBTDecorator_DurationBase : public UBTDecorator {
    GENERATED_BODY()
public:
    UEndBTDecorator_DurationBase();

};

