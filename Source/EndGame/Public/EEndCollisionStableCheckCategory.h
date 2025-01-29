#pragma once
#include "CoreMinimal.h"
#include "EEndCollisionStableCheckCategory.generated.h"

UENUM(BlueprintType)
enum class EEndCollisionStableCheckCategory : uint8 {
    System,
    Vehicle,
    Max,
};

