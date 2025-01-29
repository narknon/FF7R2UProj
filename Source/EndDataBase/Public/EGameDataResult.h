#pragma once
#include "CoreMinimal.h"
#include "EGameDataResult.generated.h"

UENUM(BlueprintType)
enum class EGameDataResult : uint8 {
    EGameDataResult_NONE,
    EGameDataResult_SUCCESS,
    EGameDataResult_ERROR,
};

