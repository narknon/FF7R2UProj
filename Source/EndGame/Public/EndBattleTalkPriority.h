#pragma once
#include "CoreMinimal.h"
#include "EndBattleTalkPriority.generated.h"

UENUM(BlueprintType)
enum class EndBattleTalkPriority : uint8 {
    Unique,
    High,
    Middle,
    Low,
    Voice_Unique,
    Voice_High,
    Voice_Mid,
    Voice_Low,
    Announce_High,
    Announce_Mid,
    Announce_Low,
    MAX,
};

