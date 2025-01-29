#pragma once
#include "CoreMinimal.h"
#include "EEndModifierType.generated.h"

UENUM(BlueprintType)
enum class EEndModifierType : uint8 {
    COVER_TYPE,
    BATTLEAREA_TYPE,
    FIELDACTION_TYPE,
    SWITCHING_TYPE,
    PATHWAY_TYPE,
    INDOOR_TYPE,
    ADDATTRIBUTE_TYPE,
    FOOTBGM_TYPE,
    ENVIRONMENT_TYPE,
    MOB_TYPE,
    HUB_TYPE,
};

