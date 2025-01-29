#pragma once
#include "CoreMinimal.h"
#include "ESQEX_AnimNotifyState_Bonamik_TemporaryCollision_CollisionType.generated.h"

UENUM(BlueprintType)
enum class ESQEX_AnimNotifyState_Bonamik_TemporaryCollision_CollisionType : uint8 {
    Box,
    Sphere,
    Capsule,
    Max,
};

