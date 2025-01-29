#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyAttachCollisionType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimNotifyAttachCollisionType : uint8 {
    DamageHit,
    PushCollision,
};

