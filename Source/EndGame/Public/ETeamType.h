#pragma once
#include "CoreMinimal.h"
#include "ETeamType.generated.h"

UENUM(BlueprintType)
enum class ETeamType : uint8 {
    TeamA,
    TeamB,
    TeamC,
    TeamD,
    Neutral,
    Max,
};

