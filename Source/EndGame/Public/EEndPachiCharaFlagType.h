#pragma once
#include "CoreMinimal.h"
#include "EEndPachiCharaFlagType.generated.h"

UENUM(BlueprintType)
enum class EEndPachiCharaFlagType : uint8 {
    SpawnOnEvent,
    DerivedMotion,
    OverwriteBindActor,
    DisableForceLOD,
};

