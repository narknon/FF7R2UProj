#pragma once
#include "CoreMinimal.h"
#include "EEndCrossSaveState.generated.h"

UENUM(BlueprintType)
enum class EEndCrossSaveState : uint8 {
    None,
    Read,
    Read_WaitSaveData,
    Upload,
    Upload_WaitTCS,
    Download,
    Download_WaitTCS,
    Write,
    Write_WaitSaveData,
    Success,
    Success_WaitEndUI,
    Error,
    Error_WaitSceError,
    Error_WaitEndUI,
};

