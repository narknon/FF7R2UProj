#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyAttachCollisionTMRule.generated.h"

UENUM(BlueprintType)
enum class EEndAnimNotifyAttachCollisionTMRule : uint8 {
    ComponentTM,
    ComponentTMSocketLocation,
    ComponentTMSocketLocationXY,
};

