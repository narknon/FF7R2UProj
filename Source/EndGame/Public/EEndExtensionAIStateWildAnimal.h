#pragma once
#include "CoreMinimal.h"
#include "EEndExtensionAIStateWildAnimal.generated.h"

UENUM(BlueprintType)
enum class EEndExtensionAIStateWildAnimal : uint8 {
    NONE,
    ITEM,
    ITEM_FOLLOWER,
    VEHICLE,
};

