#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCameraCutEndType.generated.h"

UENUM(BlueprintType)
namespace EEndBattleCameraCutEndType {
    enum Type {
        None,
        Continue,
        Loop,
        MAX,
    };
}

