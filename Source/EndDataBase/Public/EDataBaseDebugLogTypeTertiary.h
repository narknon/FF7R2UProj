#pragma once
#include "CoreMinimal.h"
#include "EDataBaseDebugLogTypeTertiary.generated.h"

UENUM(BlueprintType)
enum class EDataBaseDebugLogTypeTertiary : uint8 {
    NONE,
    GET_TYPE,
    TABLE_ID,
    NAME,
    BATTLE_CHARASPEC,
    LEVEL,
    EXP,
    GIL,
    AP,
    DROPITEM_LOTTERY,
    CHANGE_ITEM,
    CHARACTER_NAME,
    EQUIP_TYPE,
    NUM,
    MAX,
};

