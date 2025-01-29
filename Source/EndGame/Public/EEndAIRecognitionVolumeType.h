#pragma once
#include "CoreMinimal.h"
#include "EEndAIRecognitionVolumeType.generated.h"

UENUM(BlueprintType)
enum class EEndAIRecognitionVolumeType : uint8 {
    SafeArea,
    CombatArea,
    CombatAreaEnemy,
    ExcludeArea,
    Common00,
    Common01,
    Common02,
    Common03,
    Common04,
    MAX,
};

