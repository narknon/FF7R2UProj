#pragma once
#include "CoreMinimal.h"
#include "EFieldActionActorUsageStatus.generated.h"

UENUM(BlueprintType)
enum class EFieldActionActorUsageStatus : uint8 {
    Accepted,
    UseOf,
    UseNot,
    Invalid,
};

