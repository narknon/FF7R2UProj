#pragma once
#include "CoreMinimal.h"
#include "EMoogleFieldMovingPanelType.generated.h"

UENUM(BlueprintType)
enum class EMoogleFieldMovingPanelType : uint8 {
    MogPanel_Direction,
    MogPanel_SpeedScale,
    MogPanel_ReverseControl,
    Max,
};

