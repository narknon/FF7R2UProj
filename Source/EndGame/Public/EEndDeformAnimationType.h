#pragma once
#include "CoreMinimal.h"
#include "EEndDeformAnimationType.generated.h"

UENUM(BlueprintType)
enum class EEndDeformAnimationType : uint8 {
    PlayOneShot,
    PlayLoop,
    SetPosition,
    SetStartPosition,
    SetEndPosition,
    SyncAnimation,
};

