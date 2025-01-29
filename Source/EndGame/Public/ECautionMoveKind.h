#pragma once
#include "CoreMinimal.h"
#include "ECautionMoveKind.generated.h"

UENUM(BlueprintType)
namespace ECautionMoveKind {
    enum Type {
        ApproachOrLeave,
        Keep,
        Around,
    };
}

