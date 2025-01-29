#pragma once
#include "CoreMinimal.h"
#include "EEndEffectEventKind.generated.h"

UENUM(BlueprintType)
enum EEndEffectEventKind {
    EE_EK_Begin,
    EE_EK_End,
    EE_EK_LoopOff,
};

