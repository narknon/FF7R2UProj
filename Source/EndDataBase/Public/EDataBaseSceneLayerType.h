#pragma once
#include "CoreMinimal.h"
#include "EDataBaseSceneLayerType.generated.h"

UENUM(BlueprintType)
enum class EDataBaseSceneLayerType : uint8 {
    DEFAULT,
    REMEMBER,
    ZACK,
    OTHER_SCENE,
    MAX,
    NONE = MAX,
};

