#pragma once
#include "CoreMinimal.h"
#include "EEndFireEventsAtPosition.generated.h"

UENUM(BlueprintType)
enum class EEndFireEventsAtPosition : uint8 {
    AtStartOfEvaluation,
    AtEndOfEvaluation,
    AfterSpawn,
};

