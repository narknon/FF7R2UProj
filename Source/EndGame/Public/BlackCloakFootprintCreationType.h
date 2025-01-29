#pragma once
#include "CoreMinimal.h"
#include "BlackCloakFootprintCreationType.generated.h"

UENUM(BlueprintType)
enum class BlackCloakFootprintCreationType : uint8 {
    Auto,
    Hand,
    Foot,
};

