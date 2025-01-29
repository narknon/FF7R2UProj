#pragma once
#include "CoreMinimal.h"
#include "eCharacterType.generated.h"

UENUM(BlueprintType)
enum eCharacterType {
    kBiped,
    kQuadruped,
    kSnake,
    kUnstructured,
    kUnset,
};

