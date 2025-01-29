#pragma once
#include "CoreMinimal.h"
#include "EEndDialogueGenerateSourceLookAtType.generated.h"

UENUM(BlueprintType)
enum class EEndDialogueGenerateSourceLookAtType : uint8 {
    ForceEnable,
    AutoDisable,
    ForceDisable,
};

