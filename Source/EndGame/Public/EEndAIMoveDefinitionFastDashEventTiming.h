#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefinitionFastDashEventTiming.generated.h"

UENUM(BlueprintType)
enum class EEndAIMoveDefinitionFastDashEventTiming : uint8 {
    PlayLoop,
    NextMoveStart,
    ArrivedRelay,
    ArrivedLast,
};

