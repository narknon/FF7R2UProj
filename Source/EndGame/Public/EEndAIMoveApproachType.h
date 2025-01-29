#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveApproachType.generated.h"

UENUM(BlueprintType)
enum class EEndAIMoveApproachType : uint8 {
    None,
    Leave,
    Confront,
    Access,
    Around,
    Max,
};

