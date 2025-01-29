#pragma once
#include "CoreMinimal.h"
#include "EEndFootIKDisableMask.generated.h"

UENUM(BlueprintType)
enum class EEndFootIKDisableMask : uint8 {
    Notify,
    MobPrefab,
    PlannerEvent,
    Minigame,
    Menu,
    FieldAction,
    ExtraAction,
    SyncAction,
    DetachFatMoogle,
    Max,
};

