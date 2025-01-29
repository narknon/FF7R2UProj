#pragma once
#include "CoreMinimal.h"
#include "EEndNaviMapExportTextureMode.generated.h"

UENUM(BlueprintType)
enum class EEndNaviMapExportTextureMode : uint8 {
    Default,
    Export,
    FarLand,
    Retouch,
    Web,
    WebNavMesh,
};

