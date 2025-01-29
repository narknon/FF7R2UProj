#pragma once
#include "CoreMinimal.h"
#include "EEndNaviMapGenerateMode.generated.h"

UENUM(BlueprintType)
enum class EEndNaviMapGenerateMode : uint8 {
    None,
    KeepExisting,
    NavMesh,
    NavMeshLocationMap,
    StaticMeshTerrain,
    SceneCapture,
    SceneCaptureCompositeSource,
    SceneCaptureMasked,
    SceneCaptureTown,
    SceneCaptureWaterMask,
    WaterVolume,
    DebugCanvas,
};

