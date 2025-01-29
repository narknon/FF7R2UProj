#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunTeamMode.generated.h"

UENUM(BlueprintType)
enum class EEndAnimalRunTeamMode : uint8 {
    Default,
    Wild,
    GameOver,
    Max,
};

