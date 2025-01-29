#pragma once
#include "CoreMinimal.h"
#include "EEndCameraSettingLayer.generated.h"

UENUM(BlueprintType)
enum class EEndCameraSettingLayer : uint8 {
    Debug,
    Override,
    FieldAction,
    Chocobo,
    InDoor,
    Location,
    Blend,
    Default,
    MAX,
};

