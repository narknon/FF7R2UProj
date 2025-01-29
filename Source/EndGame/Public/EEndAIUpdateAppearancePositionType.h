#pragma once
#include "CoreMinimal.h"
#include "EEndAIUpdateAppearancePositionType.generated.h"

UENUM(BlueprintType)
enum class EEndAIUpdateAppearancePositionType : uint8 {
    SelfLocation,
    PopPointRandom,
};

