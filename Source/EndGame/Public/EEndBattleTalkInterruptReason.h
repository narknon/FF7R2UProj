#pragma once
#include "CoreMinimal.h"
#include "EEndBattleTalkInterruptReason.generated.h"

UENUM(BlueprintType)
enum class EEndBattleTalkInterruptReason : uint8 {
    DiffrentTalk,
    BattleEnded,
    WholeTalkSkippedWithBadStatus,
    SomeTalkSkippedWithBadStatus,
    NormalEnd,
    Notify,
    MAX,
};

