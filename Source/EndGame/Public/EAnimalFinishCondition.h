#pragma once
#include "CoreMinimal.h"
#include "EAnimalFinishCondition.generated.h"

UENUM(BlueprintType)
enum class EAnimalFinishCondition : uint8 {
    TimeUp,
    AllBallClear,
    Max,
};

