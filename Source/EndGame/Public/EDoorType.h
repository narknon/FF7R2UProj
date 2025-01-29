#pragma once
#include "CoreMinimal.h"
#include "EDoorType.generated.h"

UENUM(BlueprintType)
enum class EDoorType : uint8 {
    NormalDoor_DEPRECATED,
    PressDoor_DEPRECATED,
    AerithDoor_DEPRECATED,
    SeventhDoor_DEPRECATED,
    DoubleDoors_DEPRECATED,
    HandFirDoor_DEPRECATED,
    DoorKnobDoorVariation,
    DoubleDoorKnobDoorVariation_DEPRECATED,
    BarHandleDoorVariation,
    DoubleBarHandleDoorVariation,
    PressDoorVariation,
    DoublePressDoorVariation,
    CloudDoorKnobDoorVariation,
    CloudDoubleDoorKnobDoorVariation,
    DoublePressHeavyDoorVariation,
    MAX,
};

