#pragma once
#include "CoreMinimal.h"
#include "EDataBaseCombinationRefType.generated.h"

UENUM(BlueprintType)
enum class EDataBaseCombinationRefType : uint8 {
    Type_A,
    Type_B,
    None,
    Max = None,
};

