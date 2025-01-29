#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCameraBlendBasePosType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCameraBlendBasePosType : uint8 {
    Aim,
    Eye,
    MAX,
};

