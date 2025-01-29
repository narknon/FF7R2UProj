#pragma once
#include "CoreMinimal.h"
#include "EEndForceFeedbackPlayerMuteSlot.generated.h"

UENUM(BlueprintType)
enum class EEndForceFeedbackPlayerMuteSlot : uint8 {
    Standard,
    Extra1,
    Extra2,
    Extra3,
    FFP_MAX UMETA(Hidden),
};

