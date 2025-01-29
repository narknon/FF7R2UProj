#pragma once
#include "CoreMinimal.h"
#include "EEndAISensingCharacterType.generated.h"

UENUM(BlueprintType)
enum class EEndAISensingCharacterType : uint8 {
    Party,
    Follow,
    FieldAction,
};

