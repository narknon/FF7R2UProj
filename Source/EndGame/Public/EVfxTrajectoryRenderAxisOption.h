#pragma once
#include "CoreMinimal.h"
#include "EVfxTrajectoryRenderAxisOption.generated.h"

UENUM(BlueprintType)
enum class EVfxTrajectoryRenderAxisOption : uint8 {
    EVTRAO_RightVector,
    EVTRAO_UpVector,
    EVTRAO_BillBoard,
};

