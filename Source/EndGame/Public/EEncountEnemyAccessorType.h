#pragma once
#include "CoreMinimal.h"
#include "EEncountEnemyAccessorType.generated.h"

UENUM(BlueprintType)
enum class EEncountEnemyAccessorType : uint8 {
    EnemyAccesor,
    EncountEnemyAccessor,
    EncountAliveAndDefeatedEnemyAccessor,
    EncountAndPreEncountEnemyAccessor,
    EncountAndPreEncountAndDummyEnemyAccessor,
    EncountDummyEnemyAccessor,
    EncountHideEnemyAccessor,
    HideEnemyAccessor,
};

