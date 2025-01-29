#pragma once
#include "CoreMinimal.h"
#include "EEndNaviMapSplitNum.generated.h"

UENUM()
enum class EEndNaviMapSplitNum : int32 {
    Split_None = 1,
    Split_4 = 4,
    Split_16 = 16,
    Split_64 = 64,
    Split_MaxCsv = Split_16,
};

