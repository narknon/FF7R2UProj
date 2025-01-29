#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_RunEQSQuery.h"
#include "EndBTTask_RunEQS.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_RunEQS : public UBTTask_RunEQSQuery {
    GENERATED_BODY()
public:
    UEndBTTask_RunEQS();

};

