#pragma once
#include "CoreMinimal.h"
#include "EEndPartyCoordinatorSequence.generated.h"

UENUM(BlueprintType)
enum class EEndPartyCoordinatorSequence : uint8 {
    None,
    Initialize,
    CheckRequest,
    WaitTask,
    Finish,
};

