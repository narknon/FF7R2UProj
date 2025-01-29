#pragma once
#include "CoreMinimal.h"
#include "EEndMenuNextSaveIconKind.generated.h"

UENUM(BlueprintType)
enum class EEndMenuNextSaveIconKind : uint8 {
    None,
    CheckpointUpdated,
    FailedToSave,
    FailedToLoad,
};

