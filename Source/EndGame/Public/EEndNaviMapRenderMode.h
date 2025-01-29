#pragma once
#include "CoreMinimal.h"
#include "EEndNaviMapRenderMode.generated.h"

UENUM(BlueprintType)
enum class EEndNaviMapRenderMode : uint8 {
    Unlit,
    Lit,
    LitNoShadow,
    AllAOVs,
};

