#pragma once
#include "CoreMinimal.h"
#include "EEndAiMathCmp.generated.h"

UENUM(BlueprintType)
enum class EEndAiMathCmp : uint8 {
    Equal,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    NotEqual,
};

