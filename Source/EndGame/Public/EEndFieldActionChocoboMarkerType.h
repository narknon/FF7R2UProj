#pragma once
#include "CoreMinimal.h"
#include "EEndFieldActionChocoboMarkerType.generated.h"

UENUM(BlueprintType)
enum class EEndFieldActionChocoboMarkerType : uint8 {
    None,
    UpwardNormal,
    DownwardBillboard,
    UpwardBillboard,
    Max,
};

