#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefinitionStepExecType.generated.h"

UENUM(BlueprintType)
enum class EEndAIMoveDefinitionStepExecType : uint8 {
    None,
    PreMove,
    LeaveAftter,
    Max,
};

