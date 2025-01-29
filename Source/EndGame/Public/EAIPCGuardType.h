#pragma once
#include "CoreMinimal.h"
#include "EAIPCGuardType.generated.h"

UENUM(BlueprintType)
enum class EAIPCGuardType : uint8 {
    None,
    Normal,
    Concentrate,
};

