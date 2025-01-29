#pragma once
#include "CoreMinimal.h"
#include "EEndSituationActionFinishType.generated.h"

UENUM(BlueprintType)
enum class EEndSituationActionFinishType : uint8 {
    OneAnimation,
    EndOverlapBox,
};

