#pragma once
#include "CoreMinimal.h"
#include "EEndTakeDamageDirectionType.generated.h"

UENUM(BlueprintType)
enum class EEndTakeDamageDirectionType : uint8 {
    None,
    GiveCharacter,
    DamagePosition,
    GiveCharacterReverse,
    HitPosition,
    DamageSide,
};

