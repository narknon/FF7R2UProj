#pragma once
#include "CoreMinimal.h"
#include "EPlayerStreamStep.generated.h"

UENUM(BlueprintType)
enum class EPlayerStreamStep : uint8 {
    EPlayerStreamStep_WAIT,
    EPlayerStreamStep_REQUEST,
    EPlayerStreamStep_STREAMING,
};

