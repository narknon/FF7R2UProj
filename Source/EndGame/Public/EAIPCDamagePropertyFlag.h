#pragma once
#include "CoreMinimal.h"
#include "EAIPCDamagePropertyFlag.generated.h"

UENUM(BlueprintType)
enum class EAIPCDamagePropertyFlag : uint8 {
    None,
    Physic,
    Magic,
    All,
};

