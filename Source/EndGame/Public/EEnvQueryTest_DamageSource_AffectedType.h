#pragma once
#include "CoreMinimal.h"
#include "EEnvQueryTest_DamageSource_AffectedType.generated.h"

UENUM(BlueprintType)
enum class EEnvQueryTest_DamageSource_AffectedType : uint8 {
    Player,
    Enemy,
};

