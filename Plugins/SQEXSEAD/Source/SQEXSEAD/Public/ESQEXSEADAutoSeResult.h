#pragma once
#include "CoreMinimal.h"
#include "ESQEXSEADAutoSeResult.generated.h"

UENUM(BlueprintType)
namespace ESQEXSEADAutoSeResult {
    enum Type {
        Success,
        Failure,
        Error_InvalidArgs = 100,
        Error_InvalidBoneName,
        Error_NotAllSocketsValid,
        Error_FailedToCreateProc,
    };
}

