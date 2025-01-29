#pragma once
#include "CoreMinimal.h"
#include "EEndForceFeedbackTrack.generated.h"

UENUM(BlueprintType)
enum class EEndForceFeedbackTrack : uint8 {
    FFB_Track0,
    FFB_Track1,
    FFB_Track2,
    FFB_Track3,
    FFB_Track4,
    FFB_Track5,
    FFB_Track6,
    FFB_Track7,
    FFB_Track8,
    FFB_Track9,
    FFB_Track10,
    FFB_Track11,
    FFB_Track12,
    FFB_Track13,
    FFB_Track14,
    FFB_Track15,
    FFB_MAX UMETA(Hidden),
    FFB_AllTracks = FFB_MAX,
};

