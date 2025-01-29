#pragma once
#include "CoreMinimal.h"
#include "ESummonAbilityInfluenceCenter.generated.h"

UENUM(BlueprintType)
enum class ESummonAbilityInfluenceCenter : uint8 {
    eNone,
    eSelf,
    eTarget,
};

