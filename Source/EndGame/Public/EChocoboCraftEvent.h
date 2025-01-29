#pragma once
#include "CoreMinimal.h"
#include "EChocoboCraftEvent.generated.h"

UENUM()
enum class EChocoboCraftEvent : int32 {
    DisableEffects_Immediate,
    DisableEffects_Auto,
    ItemGet,
    ItemFound,
    SpawnHoleFA,
};

