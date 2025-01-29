#pragma once
#include "CoreMinimal.h"
#include "EDoorSoundCallPosType.generated.h"

UENUM(BlueprintType)
enum class EDoorSoundCallPosType : uint8 {
    DoorCenterGround,
    DoorAxisGround,
    DoorAxisKnobHeight,
    DoorKnob,
};

