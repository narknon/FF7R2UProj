#pragma once
#include "CoreMinimal.h"
#include "EEndMenuSaveIconKind.generated.h"

UENUM(BlueprintType)
enum class EEndMenuSaveIconKind : uint8 {
    Load,
    Save,
    List,
};

