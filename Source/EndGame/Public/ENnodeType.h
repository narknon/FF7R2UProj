#pragma once
#include "CoreMinimal.h"
#include "ENnodeType.generated.h"

UENUM()
enum class ENnodeType : int32 {
    Comment,
    Knot,
    If,
    CallFunc,
    State,
};

