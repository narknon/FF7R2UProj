#pragma once
#include "CoreMinimal.h"
#include "EAIPCTargetLocationType.generated.h"

UENUM(BlueprintType)
enum class EAIPCTargetLocationType : uint8 {
    TargetCursor,
    TargetApproach,
    CommandTargetCursor,
    CommandTargetApproach,
    CoverTargetCursor,
    CoverTargetApproach,
};

