#pragma once
#include "CoreMinimal.h"
#include "EndOnOffStatus.generated.h"

UENUM(BlueprintType)
enum class EndOnOffStatus : uint8 {
    EndOnOffStatus_On,
    EndOnOffStatus_Off,
    EndOnOffStatus_OnOverrideHide,
    EndOnOffStatus_OnHide,
    EndOnOffStatus_OnForce,
    EndOnOffStatus_OnDisable,
    EndOnOffStatus_OnOverrideHideBattle,
    EndOnOffStatus_OnPause,
    EndOnOffStatus_OnAsset,
    EndOnOffStatus_OnDrawPause,
    EndOnOffStatus_OnDisablePhysics,
    EndOnOffStatus_OnDisableCollision,
    EndOnOffStatus_OnCommandGrayOut,
};

