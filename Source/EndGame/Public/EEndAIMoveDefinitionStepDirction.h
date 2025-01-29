#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefinitionStepDirction.generated.h"

UENUM(BlueprintType)
enum class EEndAIMoveDefinitionStepDirction : uint8 {
    None,
    Back,
    Right,
    Left,
    Front,
    Max,
};

