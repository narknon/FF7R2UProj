#pragma once
#include "CoreMinimal.h"
#include "EEndNavAreaPermission.generated.h"

UENUM(BlueprintType)
namespace EEndNavAreaPermission {
    enum Type {
        WhiteList,
        BlackList,
    };
}

