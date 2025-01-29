#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCharaCategoryType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCharaCategoryType : uint8 {
    Normal,
    Shinra,
    Strong,
    ShinraStrong,
};

