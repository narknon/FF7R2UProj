#pragma once
#include "CoreMinimal.h"
#include "EEndTinyBroncoDolphinActionType.generated.h"

UENUM(BlueprintType)
enum class EEndTinyBroncoDolphinActionType : uint8 {
    SimpleJump,
    Follow,
    Max,
};

