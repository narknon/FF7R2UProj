#pragma once
#include "CoreMinimal.h"
#include "EEndAISteeringParamLayer.generated.h"

UENUM(BlueprintType)
enum class EEndAISteeringParamLayer : uint8 {
    Default,
    System,
    MiniGame,
    AIState,
    Debug,
    Max,
};

