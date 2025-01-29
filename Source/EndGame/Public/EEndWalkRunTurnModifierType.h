#pragma once
#include "CoreMinimal.h"
#include "EEndWalkRunTurnModifierType.generated.h"

UENUM(BlueprintType)
enum class EEndWalkRunTurnModifierType : uint8 {
    AIMove,
    AIStateFollow,
    AIBehaviorTree,
    CharacterControllerState,
    CharacterControllerChocobo,
};

