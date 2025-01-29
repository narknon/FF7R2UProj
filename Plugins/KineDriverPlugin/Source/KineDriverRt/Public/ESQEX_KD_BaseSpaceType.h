#pragma once
#include "CoreMinimal.h"
#include "ESQEX_KD_BaseSpaceType.generated.h"

UENUM(BlueprintType)
enum class ESQEX_KD_BaseSpaceType : uint8 {
    ESQEX_KD_BaseSpaceType_PARENT,
    ESQEX_KD_BaseSpaceType_GLOBAL,
    ESQEX_KD_BaseSpaceType_NODE,
};

