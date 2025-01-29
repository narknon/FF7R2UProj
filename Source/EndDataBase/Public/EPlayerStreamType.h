#pragma once
#include "CoreMinimal.h"
#include "EPlayerStreamType.generated.h"

UENUM(BlueprintType)
enum class EPlayerStreamType : uint8 {
    Default,
    VRSummon,
    VRSummonReturn,
};

