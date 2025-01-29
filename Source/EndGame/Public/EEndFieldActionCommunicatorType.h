#pragma once
#include "CoreMinimal.h"
#include "EEndFieldActionCommunicatorType.generated.h"

UENUM(BlueprintType)
enum class EEndFieldActionCommunicatorType : uint8 {
    None,
    FieldActionYesNo = None,
    CampBreak,
};

