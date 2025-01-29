#pragma once
#include "CoreMinimal.h"
#include "EEndLookAtRequestType.generated.h"

UENUM(BlueprintType)
enum class EEndLookAtRequestType : uint8 {
    Cinema,
    InterestAI_High,
    TargetIcon,
    AI,
    InterestAI_Low,
    BaseActionContact,
    AI_Low,
    MobPrefab,
    BaseActionIdle,
    BaseAction,
    Max,
};

