#pragma once
#include "CoreMinimal.h"
#include "EModifierVolumeCoverPostureType.generated.h"

UENUM(BlueprintType)
namespace EModifierVolumeCoverPostureType {
    enum Type {
        Stand,
        Crouch,
        Sit,
    };
}

