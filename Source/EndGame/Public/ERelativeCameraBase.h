#pragma once
#include "CoreMinimal.h"
#include "ERelativeCameraBase.generated.h"

UENUM(BlueprintType)
enum class ERelativeCameraBase : uint8 {
    ActorBase,
    LeaderBase,
    MAX,
};

