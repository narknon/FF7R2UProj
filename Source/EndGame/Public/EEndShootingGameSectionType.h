#pragma once
#include "CoreMinimal.h"
#include "EEndShootingGameSectionType.generated.h"

UENUM()
enum class EEndShootingGameSectionType : int32 {
    CreateTarget,
    CreatePhaseUI,
    MAX,
};

