#pragma once
#include "CoreMinimal.h"
#include "EHSFLipMapShapeAttributeType.generated.h"

UENUM(BlueprintType)
enum class EHSFLipMapShapeAttributeType : uint8 {
    TranslateX,
    TranslateY,
    TranslateZ,
    RotateX,
    RotateY,
    RotateZ,
    ScaleX,
    ScaleY,
    ScaleZ,
    Max,
};

