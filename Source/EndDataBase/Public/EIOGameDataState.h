#pragma once
#include "CoreMinimal.h"
#include "EIOGameDataState.generated.h"

UENUM(BlueprintType)
enum class EIOGameDataState : uint8 {
    EIOGameDataState_NONE,
    EIOGameDataState_SAVE,
    EIOGameDataState_LOAD,
    EIOGameDataState_EXIST,
    EIOGameDataState_GATHER,
    EIOGameDataState_BACKUP_SAVE,
    EIOGameDataState_BACKUP_LOAD,
    EIOGameDataState_SAVE_COMMON,
    EIOGameDataState_LOAD_COMMON,
    EIOGameDataState_GATHER_AT_SAVING,
};

