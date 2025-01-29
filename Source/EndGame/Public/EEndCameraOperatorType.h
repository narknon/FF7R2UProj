#pragma once
#include "CoreMinimal.h"
#include "EEndCameraOperatorType.generated.h"

UENUM(BlueprintType)
enum class EEndCameraOperatorType : uint8 {
    Debug,
    MenuModel,
    Menu,
    Cut,
    Dialogue,
    PlannerEvent,
    Shop,
    Rail,
    MiniGameCard,
    MiniGame,
    Sequencer,
    Battle,
    Field,
    MAX,
};

