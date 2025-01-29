#pragma once
#include "CoreMinimal.h"
#include "EEndMobPrefabMessage.generated.h"

UENUM(BlueprintType)
enum class EEndMobPrefabMessage : uint8 {
    None,
    RequestUnbind,
    StateTrigger,
};

