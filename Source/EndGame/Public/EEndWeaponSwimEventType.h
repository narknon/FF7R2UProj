#pragma once
#include "CoreMinimal.h"
#include "EEndWeaponSwimEventType.generated.h"

UENUM(BlueprintType)
enum class EEndWeaponSwimEventType : uint8 {
    MainAction,
    Branch,
    SlowlyStop,
    Reboot,
    ActionEnd,
    RequestTrigger,
    AutoReturnCamera,
    SetupCameraSpeed,
    SetupCameraRot,
    SetupAutoReturnCameraSpeedRate,
    CreateInputWaitUI,
};

