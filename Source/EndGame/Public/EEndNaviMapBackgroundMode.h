#pragma once
#include "CoreMinimal.h"
#include "EEndNaviMapBackgroundMode.generated.h"

UENUM(BlueprintType)
enum class EEndNaviMapBackgroundMode : uint8 {
    None,
    KeepExisting,
    SceneCapture,
    SceneCaptureTown,
    SceneCaptureWaterMask,
    SceneCaptureWaterMaskForceRiver,
    Silhouette,
    SilhouetteNavMesh,
};

