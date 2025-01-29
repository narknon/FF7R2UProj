#pragma once
#include "CoreMinimal.h"
#include "EBattleKeyAssignPlaceType.generated.h"

UENUM(BlueprintType)
enum class EBattleKeyAssignPlaceType : uint8 {
    None = 255,
    Ground = 0,
    Air,
};

