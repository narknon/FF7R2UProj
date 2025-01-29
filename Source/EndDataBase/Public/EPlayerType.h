#pragma once
#include "CoreMinimal.h"
#include "EPlayerType.generated.h"

UENUM(BlueprintType)
enum class EPlayerType : uint8 {
    CLOUD,
    BARRET,
    TIFA,
    AERITH,
    REDXIII,
    YUFFIE,
    CAITSITH,
    ZACK,
    SEPHIROTH,
    VINCENT,
    CID,
    AERITH_AGE7,
    Reserve_1,
    Reserve_2,
    Reserve_3,
    MAX,
    ALL = MAX,
    NONE,
};

