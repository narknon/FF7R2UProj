#pragma once
#include "CoreMinimal.h"
#include "EMoogleAITrickType.generated.h"

UENUM(BlueprintType)
enum class EMoogleAITrickType : uint8 {
    MAT_Barrage,
    MAT_TimerBom,
    MAT_Banana,
    MAT_OTHER,
};

