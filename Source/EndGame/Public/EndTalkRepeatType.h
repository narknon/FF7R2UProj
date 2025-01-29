#pragma once
#include "CoreMinimal.h"
#include "EndTalkRepeatType.generated.h"

UENUM(BlueprintType)
enum class EndTalkRepeatType : uint8 {
    PlayOnceInEncount,
    PlayOnceInPlay,
    Normal,
    MAX,
};

