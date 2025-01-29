#pragma once
#include "CoreMinimal.h"
#include "EEndDataObjectDebugFlag.generated.h"

UENUM(BlueprintType)
enum class EEndDataObjectDebugFlag : uint8 {
    NextLocationReimport,
    NextLocationSaveLocationSaveData,
};

