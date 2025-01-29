#pragma once
#include "CoreMinimal.h"
#include "EEndMenuFieldPaneType.generated.h"

UENUM(BlueprintType)
enum class EEndMenuFieldPaneType : uint8 {
    Command,
    Status,
    TypeMax,
};

