#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefinitionTakeoffAndLanding.generated.h"

UENUM(BlueprintType)
enum class EEndAIMoveDefinitionTakeoffAndLanding : uint8 {
    None,
    Takeoff,
    Landing,
};

