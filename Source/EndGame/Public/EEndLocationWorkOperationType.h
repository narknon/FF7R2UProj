#pragma once
#include "CoreMinimal.h"
#include "EEndLocationWorkOperationType.generated.h"

UENUM(BlueprintType)
enum class EEndLocationWorkOperationType : uint8 {
    Set,
    Add,
    Sub,
};

