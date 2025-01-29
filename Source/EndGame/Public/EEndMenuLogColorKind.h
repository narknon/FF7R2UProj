#pragma once
#include "CoreMinimal.h"
#include "EEndMenuLogColorKind.generated.h"

UENUM(BlueprintType)
enum class EEndMenuLogColorKind : uint8 {
    Default,
    MainStory,
    Quest,
    Report,
    Alert,
    Craft,
};

