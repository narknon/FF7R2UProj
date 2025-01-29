#pragma once
#include "CoreMinimal.h"
#include "EEndAICautionType.generated.h"

UENUM()
enum class EEndAICautionType : int32 {
    Active,
    NonActive,
    MAX,
};

