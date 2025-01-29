#pragma once
#include "CoreMinimal.h"
#include "EEndCutLogicalOperator.generated.h"

UENUM(BlueprintType)
enum class EEndCutLogicalOperator : uint8 {
    AND,
    OR,
    XOR,
};

