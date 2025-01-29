#pragma once
#include "CoreMinimal.h"
#include "ESQEXSEADSoundObjectType.generated.h"

UENUM(BlueprintType)
enum class ESQEXSEADSoundObjectType : uint8 {
    Unknown,
    Dynamic,
    Ambient,
    Direction,
    Point,
    Polygon,
    CylindricalSector,
    ShphericalEdge,
    ObstPolygon,
};

