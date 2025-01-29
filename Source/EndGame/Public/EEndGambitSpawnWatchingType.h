#pragma once
#include "CoreMinimal.h"
#include "EEndGambitSpawnWatchingType.generated.h"

UENUM(BlueprintType)
enum class EEndGambitSpawnWatchingType : uint8 {
    Watch_None,
    Watch_GambitID,
    Watch_NestLatest,
};

