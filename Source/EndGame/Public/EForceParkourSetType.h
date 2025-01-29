#pragma once
#include "CoreMinimal.h"
#include "EForceParkourSetType.generated.h"

UENUM(BlueprintType)
enum class EForceParkourSetType : uint8 {
    NaviEdgeArea,
    Spline,
    ActionMarker,
    Points,
    AttachComponent,
    Box,
    MAX,
};

