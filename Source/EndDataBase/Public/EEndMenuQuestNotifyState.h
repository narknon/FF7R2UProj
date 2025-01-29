#pragma once
#include "CoreMinimal.h"
#include "EEndMenuQuestNotifyState.generated.h"

UENUM(BlueprintType)
enum class EEndMenuQuestNotifyState : uint8 {
    None,
    Added,
    Updated,
    Completed,
};

