#pragma once
#include "CoreMinimal.h"
#include "EEndCustomCompositeReturnCondition.generated.h"

UENUM(BlueprintType)
enum class EEndCustomCompositeReturnCondition : uint8 {
    FirstSuccess,
    FirstFailure,
    LastNodeCompletes,
};

