#pragma once
#include "CoreMinimal.h"
#include "EPartyLeaderType.generated.h"

UENUM(BlueprintType)
enum class EPartyLeaderType : uint8 {
    EPartyLeaderType_Current,
    EPartyLeaderType_ForceField,
};

