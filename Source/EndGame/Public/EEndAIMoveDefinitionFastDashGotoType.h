#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefinitionFastDashGotoType.generated.h"

UENUM(BlueprintType)
enum class EEndAIMoveDefinitionFastDashGotoType : uint8 {
    TargetCharacter,
    LayoutItem,
    OwnerStart,
};

