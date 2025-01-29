#pragma once
#include "CoreMinimal.h"
#include "EOverlapTargetSection.generated.h"

UENUM(BlueprintType)
enum class EOverlapTargetSection : uint8 {
    Actor,
    Layout,
    FieldAction,
    TurnBack,
    BattleTalk,
    Vehicle,
    PlayerChara,
    MiniGame,
    AI,
    Max,
};

