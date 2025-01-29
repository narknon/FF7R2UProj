#pragma once
#include "CoreMinimal.h"
#include "EEndDoOnceOutCode.generated.h"

UENUM(BlueprintType)
enum class EEndDoOnceOutCode : uint8 {
    First,
    Other,
    Reset,
};

