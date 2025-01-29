#pragma once
#include "CoreMinimal.h"
#include "EEndStateTriggerSaveDataType.generated.h"

UENUM(BlueprintType)
enum class EEndStateTriggerSaveDataType : uint8 {
    None,
    SnapSaveData,
    SafetySaveData_AutoSaveData,
    AutoSaveData,
    SnapSaveData_AutoSaveData,
    SnapSaveData_SafetySaveData_AutoSaveData,
    SnapOutput_SafetySaveData_AutoSaveData,
    SnapOutput_AutoSaveData,
    SnapSaveData_Encount,
    SnapSaveData_Force,
};

