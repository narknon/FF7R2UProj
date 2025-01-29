#pragma once
#include "CoreMinimal.h"
#include "EEndMenuStoryNotifyState.generated.h"

UENUM(BlueprintType)
enum class EEndMenuStoryNotifyState : uint8 {
    None,
    Added,
    Completed,
};

