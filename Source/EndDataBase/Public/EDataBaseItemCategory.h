#pragma once
#include "CoreMinimal.h"
#include "EDataBaseItemCategory.generated.h"

UENUM()
enum class EDataBaseItemCategory {
    NONE = -1,
    USE = 0,
    MATERIAL,
    KEYITEM,
    WEAPON,
    ARMOR,
    ACCESSORY,
    MATERIA,
    JUKEBOX,
    CURRENCY,
    COSTUME,
    RECIPEBOOK,
    SKILLBOOK,
    CHOCOBOACCESSORY,
    QBCARD,
    TROPHY,
    MAX,
};

