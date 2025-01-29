#pragma once
#include "CoreMinimal.h"
#include "EEnvEffectGeneratePosition.generated.h"

UENUM(BlueprintType)
enum class EEnvEffectGeneratePosition : uint8 {
    None,
    Center,
    Hit,
};

