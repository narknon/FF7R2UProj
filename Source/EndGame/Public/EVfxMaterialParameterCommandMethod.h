#pragma once
#include "CoreMinimal.h"
#include "EVfxMaterialParameterCommandMethod.generated.h"

UENUM(BlueprintType)
enum class EVfxMaterialParameterCommandMethod : uint8 {
    MPCM_None,
    MPCM_Set,
    MPCM_Multiply,
    MPCM_Add,
};

