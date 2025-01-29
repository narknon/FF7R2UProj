#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "EndBTD_IsSummonAcceptingCommands.generated.h"

UCLASS(Blueprintable)
class UEndBTD_IsSummonAcceptingCommands : public UBTDecorator {
    GENERATED_BODY()
public:
    UEndBTD_IsSummonAcceptingCommands();

};

