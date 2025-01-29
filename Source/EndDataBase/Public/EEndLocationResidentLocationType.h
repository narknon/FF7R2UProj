#pragma once
#include "CoreMinimal.h"
#include "EEndLocationResidentLocationType.generated.h"

UENUM(BlueprintType)
enum class EEndLocationResidentLocationType : uint8 {
    EEndLocationResidentLocationType_Sub,
    EEndLocationResidentLocationType_Main,
    EEndLocationResidentLocationType_Data,
    EEndLocationResidentLocationType_DebugMain,
};

