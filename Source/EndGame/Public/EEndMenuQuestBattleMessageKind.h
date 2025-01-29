#pragma once
#include "CoreMinimal.h"
#include "EEndMenuQuestBattleMessageKind.generated.h"

UENUM(BlueprintType)
enum class EEndMenuQuestBattleMessageKind : uint8 {
    TargetDiscovered,
    TargetDestroyed,
    ClientDiscovered,
};

