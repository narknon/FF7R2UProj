#pragma once
#include "CoreMinimal.h"
#include "ESimpleInteractTarget.generated.h"

UENUM(BlueprintType)
enum class ESimpleInteractTarget : uint8 {
    ESITarget_SelfActor,
    ESITarget_InteractActor,
    ESITarget_World,
};

