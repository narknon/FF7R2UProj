#pragma once
#include "CoreMinimal.h"
#include "EDataBaseDebugLogGetType.generated.h"

UENUM(BlueprintType)
enum class EDataBaseDebugLogGetType : uint8 {
    NONE,
    ACTION,
    HUB_STORY,
    HUB_NOTIFIER,
};

