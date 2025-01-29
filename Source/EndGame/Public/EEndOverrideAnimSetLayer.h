#pragma once
#include "CoreMinimal.h"
#include "EEndOverrideAnimSetLayer.generated.h"

UENUM(BlueprintType)
enum class EEndOverrideAnimSetLayer : uint8 {
    MiniGame,
    FieldMotion,
    StateManager,
    Battle,
    Field,
    AIBehavior,
    AIMove,
    Vehicle,
    Basic,
    WildAnimal,
    Debug,
    Max,
};

