#pragma once
#include "CoreMinimal.h"
#include "EAIInfoParam.generated.h"

UENUM(BlueprintType)
namespace EAIInfoParam {
    enum Type {
        eLOOKAT_START_DISTANCE,
        eLOOKAT_END_DISTANCE,
        eLOOKAT_START_ANGLE,
        eLOOKAT_END_ANGLE,
        eINTERVAL_MOVE_TIME,
        eWAIT_MOVE_TIME,
        eFOLLOW_DISTANCE,
        eFOLLOW_RUN_DISTANCE,
        eMAX,
    };
}

