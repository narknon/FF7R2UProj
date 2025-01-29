#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCameraSLerpType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCameraSLerpType : uint8 {
    None,
    Satellite,
    Cylinder,
};

