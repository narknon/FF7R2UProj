#pragma once
#include "CoreMinimal.h"
#include "EEndBodySubCollisionCategory.generated.h"

UENUM(BlueprintType)
enum class EEndBodySubCollisionCategory : uint8 {
    BehaviorMode,
    Field,
    Max,
};

