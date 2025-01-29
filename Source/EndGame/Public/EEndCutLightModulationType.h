#pragma once
#include "CoreMinimal.h"
#include "EEndCutLightModulationType.generated.h"

UENUM(BlueprintType)
enum class EEndCutLightModulationType : uint8 {
    EnvironmentLight,
    DirectionalLight,
};

