#pragma once
#include "CoreMinimal.h"
#include "EEndEncountStateType.generated.h"

UENUM(BlueprintType)
enum class EEndEncountStateType : uint8 {
    None,
    Normal,
    OnCaution,
    Battle,
    Escaping,
    Max,
};

