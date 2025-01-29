#pragma once
#include "CoreMinimal.h"
#include "EEndAISensorDangerObjectAttachType.generated.h"

UENUM(BlueprintType)
enum class EEndAISensorDangerObjectAttachType : uint8 {
    Off,
    OnlyInit,
    On,
};

