#pragma once
#include "CoreMinimal.h"
#include "EEndFieldManagerSetupWaitRetryType.generated.h"

UENUM(BlueprintType)
enum class EEndFieldManagerSetupWaitRetryType : uint8 {
    None,
    WaitCharaAttach,
    WaitMassiveStreaming,
    WaitTextureStreaming,
    WaitCharaPopUpdateTickLOD,
    WaitCharaPopStableTimer,
};

