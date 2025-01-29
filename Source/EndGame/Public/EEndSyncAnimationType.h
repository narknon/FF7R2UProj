#pragma once
#include "CoreMinimal.h"
#include "EEndSyncAnimationType.generated.h"

UENUM(BlueprintType)
enum class EEndSyncAnimationType : uint8 {
    MasterSlave,
    TimeLink,
    MasterSlaveTimeLink,
};

