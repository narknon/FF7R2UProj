#pragma once
#include "CoreMinimal.h"
#include "EEndSimpleInteractStateControllerType.generated.h"

UENUM(BlueprintType)
namespace EEndSimpleInteractStateControllerType {
    enum Type {
        Actor,
        Player,
        Max,
    };
}

