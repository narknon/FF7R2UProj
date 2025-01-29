#pragma once
#include "CoreMinimal.h"
#include "EEndAnimUpdateType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimUpdateType : uint8 {
    Default,
    Rope,
    WildAnimal,
    Chocobo,
    ChocoboRider,
};

