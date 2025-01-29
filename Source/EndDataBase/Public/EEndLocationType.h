#pragma once
#include "CoreMinimal.h"
#include "EEndLocationType.generated.h"

UENUM(BlueprintType)
enum class EEndLocationType : uint8 {
    EEndLocationType_Main,
    EEndLocationType_Sub,
    EEndLocationType_Common,
    EEndLocationType_DebugMain,
};

