#pragma once
#include "CoreMinimal.h"
#include "EEndMenuChocoboStableMenuType.generated.h"

UENUM(BlueprintType)
enum class EEndMenuChocoboStableMenuType : uint8 {
    Normal,
    Race,
    RaceDirect,
    RaceNonCancellable,
};

