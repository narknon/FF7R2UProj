#pragma once
#include "CoreMinimal.h"
#include "EEndAutoFootLockModifierType.generated.h"

UENUM(BlueprintType)
enum class EEndAutoFootLockModifierType : uint8 {
    None,
    ForceEnable,
    ForceDisable,
};

