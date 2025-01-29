#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSummonAppearType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleSummonAppearType : uint8 {
    Jump,
    Fly,
    Special,
    Odin,
    Ground,
    Shiva,
    Phoenix,
    Ifrit,
};

