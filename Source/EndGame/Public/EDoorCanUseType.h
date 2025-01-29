#pragma once
#include "CoreMinimal.h"
#include "EDoorCanUseType.generated.h"

UENUM(BlueprintType)
enum class EDoorCanUseType : uint8 {
    All,
    OnlyLeader,
    OnlyNpc,
};

