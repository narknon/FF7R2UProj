#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveNavPropertyType.generated.h"

UENUM(BlueprintType)
enum class EEndAIMoveNavPropertyType : uint8 {
    Character,
    Normal,
    NormalField,
    NormalBattle,
};

