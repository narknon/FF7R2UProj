#pragma once
#include "CoreMinimal.h"
#include "EEndMenuInputGuidelineType.generated.h"

UENUM(BlueprintType)
enum class EEndMenuInputGuidelineType : uint8 {
    Attack,
    BindUnleash,
    CharacterChange,
    TypeMax,
};

