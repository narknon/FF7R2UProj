#pragma once
#include "CoreMinimal.h"
#include "EAutoDoorStatus.generated.h"

UENUM(BlueprintType)
enum class EAutoDoorStatus : uint8 {
    CLOSING,
    OPENING,
    MAX,
};

