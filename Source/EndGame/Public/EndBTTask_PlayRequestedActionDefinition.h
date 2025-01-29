#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EndBTTask_PlayRequestedActionDefinition.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_PlayRequestedActionDefinition : public UBTTask_BlackboardBase {
    GENERATED_BODY()
public:
    UEndBTTask_PlayRequestedActionDefinition();

};

