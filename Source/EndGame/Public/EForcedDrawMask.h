#pragma once
#include "CoreMinimal.h"
#include "EForcedDrawMask.generated.h"

UENUM(BlueprintType)
enum class EForcedDrawMask : uint8 {
    EForcedDrawMask_CINEMA,
    EForcedDrawMask_DEBUG,
};

