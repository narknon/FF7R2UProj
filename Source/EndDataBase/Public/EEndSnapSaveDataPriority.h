#pragma once
#include "CoreMinimal.h"
#include "EEndSnapSaveDataPriority.generated.h"

UENUM(BlueprintType)
enum class EEndSnapSaveDataPriority : uint8 {
    None,
    MainMenuSave,
    SnapSave2nd,
    EncountCaution,
    MainMenuClose,
    EncountStart,
    ActionControlLift,
    LevelPlanner,
    ForceLevelPlanner,
};

