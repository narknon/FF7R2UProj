#pragma once
#include "CoreMinimal.h"
#include "EPlayerSpecType.generated.h"

UENUM(BlueprintType)
enum class EPlayerSpecType : uint8 {
    Normal,
    Reserve,
    NoBattle,
    Max,
};

